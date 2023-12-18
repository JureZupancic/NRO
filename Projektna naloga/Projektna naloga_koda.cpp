// Projektna naloga_koda.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <omp.h>
#include <ctime>
#include <map>
#include <regex>

using namespace std;

int main()
{
    std::string filename = "./primer3mreza.txt";

    std::vector<double> X;
    std::vector<double> Y;
    std::vector<vector<int>> celice;
    std::map<int, std::vector<int>> vozlisca_robnih_pogojev;
    std::vector<int> tipi_robnih_pogojev;
    std::vector<double> vrednosti_robnih_pogojev;
    std::vector<double> vrednosti_prestopa_toplote;

    

    std::ifstream file;
    file.open(filename);
    std::string str_tocke;
    std::ifstream indata;
    indata >> str_tocke;
    std::string str_points;
    indata >> str_points;
    int n_vozlisc = std::stoi(str_points); //Št. vozlišč

//Branje vozlišč

    for (int i = 0; i < n_vozlisc; i++) {
        std::string s;
        std::getline(file, s); // preberemo vrstico
        std::replace(s.begin(), s.end(), ';', ' ');
        std::replace(s.begin(), s.end(), ',', ' ');
        std::istringstream iss(s);
        int node_id;
        double x;
        double y;
        iss >> node_id >> x >> y;


        X.push_back(x);
        Y.push_back(y);
    }

    /*
    // Print the resulting vectors
    for (int i = 0; i < X.size(); i++) {
        std::cout << "X[" << i << "] = " << X[i] << std::endl;
        std::cout << "Y[" << i << "] = " << Y[i] << std::endl;
    }
    */

    std::string prazna_vrstica;
    std::getline(file, prazna_vrstica);

//Branje celic

    std::string cell_line;
    std::getline(file, cell_line);

    std::vector<std::string> cells_string;
    std::string cell;
    std::istringstream iss(cell_line);
    while (iss >> cell) {
        cells_string.push_back(cell);
    }
    int n_celice = std::stoi(cells_string[1]);
    
    for (int i = 0; i < n_celice; i++) {
        std::string s;
        std::getline(file, s); // preberemo vrstico
        std::replace(s.begin(), s.end(), ';', ' ');
        std::replace(s.begin(), s.end(), ',', ' ');
        std::istringstream iss(s);
        int cell_id;
        int node1_id;
        int node2_id;
        int node3_id;
        int node4_id;
        iss >> cell_id >>node1_id >> node2_id >> node3_id >> node4_id;
        vector<int> celica;

        celica.push_back(cell_id);
        celica.push_back(node1_id);
        celica.push_back(node2_id);
        celica.push_back(node3_id);
        celica.push_back(node4_id);

        celice.push_back(celica);
        
    }

    std::string prazna_vrstica;
    std::getline(file, prazna_vrstica);

// Branje robnih pogojev

    std::string robni_pogoji_line;
    std::getline(file, robni_pogoji_line);

    std::vector<std::string> robni_pogoji_string;
    std::string rp;
    std::istringstream iss(robni_pogoji_line);
    while (iss >> rp) {
        robni_pogoji_string.push_back(rp);
    }
    int n_pogoji = std::stoi(robni_pogoji_string[1]);

    for (int i = 0; i < n_pogoji; i++) {
        std::string s;
        string tip_pogoja;
        std::getline(file, s); // preberemo vrstico
        std::cout << "pogoj 1:" << tip_pogoja << "\n";

        if (tip_pogoja == "temperatura") {
            tipi_robnih_pogojev.push_back(0);
            int temperatura = 0;
            std::cout << "temperatura:" << temperatura << "\n";

            vrednosti_robnih_pogojev.push_back(temperatura);
            vrednosti_prestopa_toplote.push_back(-1);
            
        }

        else if (tip_pogoja == "toplotni") {
            tipi_robnih_pogojev.push_back(1);
            int toplotni_tok = 0;
            std::cout << "toplotni tok:" << toplotni_tok << "\n";

            vrednosti_robnih_pogojev.push_back(toplotni_tok);
            vrednosti_prestopa_toplote.push_back(-1);

        }

        else if (tip_pogoja == "prestop") {
            tipi_robnih_pogojev.push_back(2);
            int temp_prestopa = 0;
            int koef_prestopa = 0;
            std::cout << "temperatura:" << temp_prestopa << "\n";
            std::cout << "koeficient prestopa:" << koef_prestopa << "\n";

            vrednosti_robnih_pogojev.push_back(temp_prestopa);
            vrednosti_prestopa_toplote.push_back(koef_prestopa);

        }

        int st_vozlisc_v_rp;
        std::cout << st_vozlisc_v_rp << "\n";

        vector<int> vozlisca_v_robnem_pogoju;

        for (int i; i < st_vozlisc_v_rp; i++) {
            int id_vozlisca;
            std::cout << id_vozlisca << "\n";

            vozlisca_v_robnem_pogoju.push_back(id_vozlisca);

        }

        vozlisca_robnih_pogojev.insert({ i, vozlisca_v_robnem_pogoju });
       
    }

// Tu je konec branja datoteke

    int deltaX = 1;
    int deltaY = 1;
    double k = 1;

    vector<double> sosednja_vozlisca;

    for (int node_id = 0; node_id < n_vozlisc; node_id++;) {
        vector<double> node_i_neighbours = (-1, -1, -1, -1);

        for (int nd = 0; nd < n_celice; nd++;) {
            vector<int> trenutna_celica = celice[nd];

            int vozclisce1 = trenutna_celica(0);
            int vozclisce2 = trenutna_celica(1);
            int vozclisce3 = trenutna_celica(2);
            int vozclisce4 = trenutna_celica(3);

            if (node_id == vozlisce1; node_id == vozlisce2; node_id == vozlisce3; node_id == vozlisce4) {
                for (int vozl = 0; vozl < 4, vozl++;) {
                    int sosednje_vozlisce = trenutna_celica(vozl);

                    int pozicija;

                    if (sosednje_vozlisce ~= node_id;) {
                        int x_obravnavano_vozl = X(node_id);
                        int y_obravnavano_vozl = Y(node_id);

                        int x_sosed = X(sosednja_vozlisca);
                        int y_sosed = Y(sosednja_vozlisca);

                        if ((x_obravnavano_vozl - x_sosed) < 1e-9 && (x_obravnavano_vozl - x_sosed) < -1e-9;) {
                            if ((y_obravnavano_vozl - y_sosed) < 0;) {
                                pozicija = 2;
                            }
                            else {
                                pozicija = 4;
                            }
                        }

                        else if ((y_obravnavano_vozl - y_sosed) < 1e-9 && (y_obravnavano_vozl - y_sosed) < -1e-9;) {
                            if ((x_obravnavano_vozl - x_sosed) < 0;) {
                                pozicija = 1;
                            }
                            else {
                                pozicija = 3;
                            }
                        }

                        else {
                            pozicija = -1;
                        }
                        
                    }
                    if (pozicija ~= -1) {
                        node_i_neighbours(pozicija) = sosednja_vozlisce;
                    }
                }
            }
        }
        sosednja_vozlisca = [sosednja_vozlisca; node_i_neighbours];
    }
    
    vector<vector<double>> A;
    
    for (int r = 0; r < n_vozlisc; r++;) {
        vector<double> cols;
        for (int c = 0; c < n_vozlisc; c++;) {
            cols = cols[cols; 0];
        }
        A.push_back(cols, ;);
    }

    vector<double> b;
    for (r = 0; r < n_vozlisc, r++;) {
        b = [b; 0];
    }

    //vector<double> sosedi;
    for (int node_id = 0; node_id < n_vozlisc; node_id++;) {
        vector<double> sosedi = sosednja_vozlisca(node_id, :);
        int levi_sosed = sosedi(0);
        int spodnji_sosed = sosedi(1);
        int desni_sosed = sosedi(2);
        int zgornji_sosed = sosedi(3);

        if (levi_sosed ~= -1 && spodnji_sosed ~= -1 && desni_sosed ~= -1 && zgornji_sosed ~= -1;) {
            A(node_id, levi_sosed) = 1;
            A(node_id, spodnji_sosed) = 1;
            A(node_id, desni_sosed) = 1;
            A(node_id, zgornji_sosed) = 1;
            A(node_id, node_id) = -4;
        }
        else {
            int tip_robnega_pogoja;
            vector<double> vrednost;
            vector<double> vrednost_prestopa;

            for (int robni_pogoji_id = 0; robni_pogoji_id < n_pogoji; robni_pogoji_id++;) {
                vector<int> vozlisca_v_trenutnem_rp = vozlisca_robnih_pogojev[robni_pogoj_id];

                for (int id_vozlisce_rp = 0; id_vozlisce_rp < size(vozlisca_v_trenutnem_rp); id_vozlisce_rp++;) {
                    vozlisca_v_trenutnem_rp = vozlisca_v_trenutnem_rp(id_vozlisce_rp);

                    if (node_id == vozlisca_v_trenutnem_rp;) {
                        tip_robnega_pogoja = tipi_robnih_pogojev(robni_pogoj_id);

                        vrednost = vrednosti_robnih_pogojev(robni_pogoji_id);

                        vrednost_prestopa = vrednosti_prestopa_toplote(robni_pogoji_id);
                    }
                }
            }

            if (tip_robnega_pogoja == 0;) {
                A(node_id, node_id) = 1;
                b(node_id) = vrednost;
            }

            else if (tip_robnega_pogoja == 1;) {
                int stevilo_sosedov = 0;

                for (int st = 0; st < 4; st++;) {
                    if (sosedi(st) ~= -1;) {
                        stevilo_sosedov = stevilo_sosedov + 1;
                    }
                }

                if (stevilo_sosedov == 3;) {
                    if (levi_sosed == -1;) {
                        A(node_id, node_id) = A(node_id, node_id) - 4;
                        A(node_id, desni_sosed) = A(node_id, desni_sosed) + 2;
                        A(node_id, spodnji_sosed) = A(node_id, spodnji_sosed) + 1;
                        A(node_id, zgornji_sosed) = A(node_id, zgornji_sosed) + 1;
                        b(node_id) = -2 * (vrednost * deltaX / k);
                    }
                    if (desni_sosed == -1;) {
                        A(node_id, node_id) = A(node_id, node_id) - 4;
                        A(node_id, levi_sosed) = A(node_id, levi_sosed) + 2;
                        A(node_id, spodnji_sosed) = A(node_id, spodnji_sosed) + 1;
                        A(node_id, zgornji_sosed) = A(node_id, zgornji_sosed) + 1;
                        b(node_id) = -2 * (vrednost * deltaX / k);
                    }
                    if (spodnji_sosed == -1;) {
                        A(node_id, node_id) = A(node_id, node_id) - 4;
                        A(node_id, spodnji_sosed) = A(node_id, spodnji_sosed) + 2;
                        A(node_id, levi_sosed) = A(node_id, levi_sosed) + 1;
                        A(node_id, desni_sosed) = A(node_id, desni_sosed) + 1;
                        b(node_id) = -2 * (vrednost * deltaX / k);
                    }
                }
            }

            else if (tip_robnega_pogoja == 2;) {
                int stevilo_sosedov = 0;
                for (int st = 0; st < 4; st++;) {
                    if (sosedi(st) ~= -1;) {
                        stevilo_sosedov = stevilo_sosedov + 1;
                    }
                }

                if (stevilo_sosedov == 3;) {
                    if (levi_sosed == -1;) {
                        A(node_id, node_id) = A(node_id, node_id) - 2 * (vrednost_prestopa * deltaX / k + 2);
                        A(node_id, desni_sosed) = A(node_id, desni_sosed) + 2;
                        A(node_id, spodnji_sosed) = A(node_id, spodnji_sosed) + 1;
                        A(node_id, zgornji_sosed) = A(node_id, zgornji_sosed) + 1;
                        b(node_id) = b(node_id) - 2 * vrednost_prestopa * deltaX * vrednost / k;
                    }

                    if (desni_sosed == -1;) {
                        A(node_id, node_id) = A(node_id, node_id) - 2 * (vrednost_prestopa * deltaX / k + 2);
                        A(node_id, levi_sosed) = A(node_id, levi_sosed) + 2;
                        A(node_id, spodnji_sosed) = A(node_id, spodnji_sosed) + 1;
                        A(node_id, zgornji_sosed) = A(node_id, zgornji_sosed) + 1;
                        b(node_id) = b(node_id) - 2 * vrednost_prestopa * deltaX * vrednost / k;
                    }

                    if (spodnji_sosed == -1;) {
                        A(node_id, node_id) = A(node_id, node_id) - 2 * (vrednost_prestopa * deltaX / k + 2);
                        A(node_id, levi_sosed) = A(node_id, levi_sosed) + 1;
                        A(node_id, desni_sosed) = A(node_id, desni_sosed) + 1;
                        A(node_id, zgornji_sosed) = A(node_id, zgornji_sosed) + 2;
                        b(node_id) = -2 * vrednost_prestopa * deltaX * vrednost / k;
                    }

                    if (zgornji_sosed == -1;) {
                        A(node_id, node_id) = A(node_id, node_id) - 2 * (vrednost_prestopa * deltaX / k + 2);
                        A(node_id, levi_sosed) = A(node_id, levi_sosed) + 1;
                        A(node_id, desni_sosed) = A(node_id, desni_sosed) + 1;
                        A(node_id, spodnji_sosed) = A(node_id, spodnji_sosed) + 2;
                        b(node_id) = -2 * vrednost_prestopa * deltaX * vrednost / k;
                    }
                }
            }
        }
    }

    //Sedaj imamo matriko A in vektor b. jupi


    std::cout << n_vozlisc;


    std::cout << "Hello World!\n";
}

