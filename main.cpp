#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QStack>
#include <string>
#include <cstring>
#include <stack>
#include <ostream>
#include "NodeBoolTree.h"
#include "boolinterval.h"
#include "boolequation.h"
#include "BBV.h"

using namespace std;

int main(int argc, char *argv[])
{
    QStringList full_file_list;
    std::string filepath = "/home/kali/Desktop/AllocatorIntegrationConsoleApp/SAT_DPLL/SatExamples/Sat_ex14_3.pla";
    QFile file(QString::fromUtf8(filepath.c_str()));

    if ((file.exists()) && (file.open(QIODevice::ReadOnly))) {
        while (!file.atEnd()) {
            full_file_list << file.readLine().replace("\r\n", "");
        }

        int cnfSize = full_file_list.length();
        BoolInterval **CNF = new BoolInterval*[cnfSize];
        int rangInterval = -1;

        if (cnfSize) {
            rangInterval = full_file_list[0].toUtf8().trimmed().length();
        }

        for (int i = 0; i < cnfSize; i++) {
            QString strv = full_file_list[i];
            CNF[i] = new BoolInterval(strv.toUtf8().trimmed().data());
        }

        QString rootvec = "";
        QString rootdnc = "";
        for (int i = 0; i < rangInterval; i++) {
            rootvec += "0";
            rootdnc += "1";
        }
        QByteArray v = rootvec.toUtf8();
        BBV vec(v.data());
        QByteArray d = rootdnc.toUtf8();
        BBV dnc(d.data());

        BoolInterval *root = new BoolInterval(vec, dnc);
        BoolEquation *boolequation = new BoolEquation(CNF, root, cnfSize, cnfSize, vec);

        // Назначаем стратегию через сеттер
        boolequation->SetStrategy(new ColumnStrategy());

        bool rootIsFinded = false;
        stack<NodeBoolTree *> BoolTree;
        NodeBoolTree *startNode = new NodeBoolTree(boolequation);
        BoolTree.push(startNode);

        do {
            NodeBoolTree *currentNode = BoolTree.top();

            if (currentNode->lt == nullptr && currentNode->rt == nullptr) {
                // Используем геттер для получения BoolEquation
                BoolEquation *currentEquation = currentNode->eq;
                // Если стратегия не назначена, назначаем её
                if (currentEquation->GetStrategy() == nullptr) {
                    currentEquation->SetStrategy(new ColumnStrategy());
                }
                bool flag = true;
                while (flag) {
                    int a = currentEquation->CheckRules();

                    switch (a) {
                        case 0: {
                            BoolTree.pop();
                            flag = false;
                            break;
                        }
                        case 1: {
                            if (currentEquation->GetCount() == 0 ||
                                currentEquation->GetMask().getWeight() == currentEquation->GetMask().getSize()) {
                                flag = false;
                                rootIsFinded = true;
                                for (int i = 0; i < cnfSize; i++) {
                                    if (!CNF[i]->isEqualComponent(*currentEquation->GetRoot())) {
                                        rootIsFinded = false;
                                        BoolTree.pop();
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                        case 2: {
                            int indexBranching = currentEquation->GetStrategy()->chooseVarForBranching(currentEquation);
                            if (indexBranching < 0) {
                                flag = false;
                                break;
                            }
                            BoolEquation *Equation0 = new BoolEquation(*currentEquation);
                            BoolEquation *Equation1 = new BoolEquation(*currentEquation);

                            Equation0->Simplify(indexBranching, '0');
                            Equation1->Simplify(indexBranching, '1');

                            NodeBoolTree *Node0 = new NodeBoolTree(Equation0);
                            NodeBoolTree *Node1 = new NodeBoolTree(Equation1);

                            currentNode->lt = Node0;
                            currentNode->rt = Node1;

                            BoolTree.push(Node1);
                            BoolTree.push(Node0);

                            flag = false;
                            break;
                        }
                    }
                }
            } else {
                BoolTree.pop();
            }
        } while (BoolTree.size() > 1 && !rootIsFinded);

        if (rootIsFinded) {
            cout << "Root is:\n ";
            BoolInterval *finded_root = BoolTree.top()->eq->GetRoot();
            cout << string(*finded_root);
        } else {
            cout << "Root does not exist!";
        }
    } else {
        cout << "File does not exist.\n";
    }
    return 0;
}
