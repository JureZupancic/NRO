// Projektna naloga_koda.cpp

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
    std::string filename = "./primer1mreza.txt";

    std::vector<double> X;
    std::vector<double> Y;
    std::vector<vector<int>> celice;
    std::vector<vector<int>> vozlisca_robnih_pogojev;
    std::vector<int> tipi_robnih_pogojev;
    std::vector<double> vrednosti_robnih_pogojev;
    std::vector<double> vrednosti_prestopa_toplote;

    std::ifstream file;
    file.open(filename);

    std::string string_first_line;
    std::getline(file, string_first_line);

    std::istringstream iss(string_first_line);
    std::string nepomemben_del1;

//Branje števila vozlišč

    int n_vozlisc;

    iss >> nepomemben_del1;
    iss >> n_vozlisc;

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

    
    std::string prazna_vrstica;
    std::getline(file, prazna_vrstica);

//Branje celic

    std::string cell_line;
    std::getline(file, cell_line);

    std::vector<std::string> cells_string;
    std::string cell;
    std::istringstream iss2(cell_line);
    while (iss2 >> cell) {
        cells_string.push_back(cell);
    }
    int n_celice = std::stoi(cells_string[1]);
    
    for (int i = 0; i < n_celice; i++) {
        std::string s;
        std::getline(file, s); 
        std::replace(s.begin(), s.end(), ';', ' ');
        std::replace(s.begin(), s.end(), ',', ' ');
        std::istringstream iss(s);
        int cell_id;
        int node1_id;
        int node2_id;
        int node3_id;
        int node4_id;
        iss >> cell_id >> node1_id >> node2_id >> node3_id >> node4_id;
        vector<int> celica;

        celica.push_back(node1_id);
        celica.push_back(node2_id);
        celica.push_back(node3_id);
        celica.push_back(node4_id);

        celice.push_back(celica);
        
    }

//Branje robnih pogojev

    std::string prazna_vrstica2;
    std::getline(file, prazna_vrstica2);

    std::string robni_pogoji_line;
    std::getline(file, robni_pogoji_line);

    std::vector<std::string> robni_pogoji_string;
    std::string rp;
    std::istringstream iss3(robni_pogoji_line);

    int n_pogoji=0;
    std::string nepomemben_del2;
    std::string nepomemben_del3;

    iss3 >> nepomemben_del2;
    iss3 >> nepomemben_del3;
    iss3 >> n_pogoji;

    for (int i = 0; i < n_pogoji; i++) {
        std::string s;
        string whatever;
        string tip_pogoja;
        std::getline(file, s);
        std::istringstream iss4(s);
        std::string npd1;
        std::string npd2;
        iss4 >> npd1;
        iss4 >> npd2;
        iss4 >> tip_pogoja;

//Branje datoteke, če imamo opravka z znano temperaturo na robu
        
        if (tip_pogoja == "temperatura") {
            tipi_robnih_pogojev.push_back(0);
            std::string rp_temp;
            std::getline(file, rp_temp);
            std::istringstream issrp1(rp_temp);
            double temperatura;
            std::string nepomemben_del4;

            issrp1 >> nepomemben_del4;
            issrp1 >> temperatura;

            vrednosti_robnih_pogojev.push_back(temperatura);
            vrednosti_prestopa_toplote.push_back(-1);
            
        }

//Branje datoteke, če imamo opravka z toplotnim tokom na robu

        else if (tip_pogoja == "toplotni") {
            tipi_robnih_pogojev.push_back(1);
            std::string rp_q;
            std::getline(file, rp_q);
            std::istringstream issrp2(rp_q);
            double toplotni_tok = 0;

            std::string nepomemben_del4;

            issrp2 >> nepomemben_del4;
            issrp2 >> toplotni_tok;

            vrednosti_robnih_pogojev.push_back(toplotni_tok);
            vrednosti_prestopa_toplote.push_back(-1);

        }

//Branje datoteke, če imamo opravka z konvektivnim prestopom na robu

        else if (tip_pogoja == "prestop") {
            tipi_robnih_pogojev.push_back(2);
            std::string rp_prest;
            std::getline(file, rp_prest);
            std::istringstream issrp3(rp_prest);

            double temp_prestopa = 0;
            double koef_prestopa = 0;

            std::string nepomemben_del4;
            std::string nepomemben_del5;

            issrp3 >> nepomemben_del4 >> temp_prestopa;
            std::string rp_prest2;
            std::getline(file, rp_prest2);
            std::istringstream issrp4(rp_prest2);

            issrp4 >> nepomemben_del5 >> koef_prestopa;

            vrednosti_robnih_pogojev.push_back(temp_prestopa);
            vrednosti_prestopa_toplote.push_back(koef_prestopa);

        }

        int st_vozlisc_v_rp=0; 

        std::string st_vozlisc_rp;
        std::getline(file, st_vozlisc_rp);
        std::istringstream strp(st_vozlisc_rp);

        strp >> st_vozlisc_v_rp;

        vector<int> vozlisca_v_robnem_pogoju;

        for (int i = 0; i < st_vozlisc_v_rp; i++) {

            std::string id_voz_rp;
            std::getline(file, id_voz_rp);
            std::istringstream idvozrp(id_voz_rp);

            int id_vozlisca = 0;

            idvozrp >> id_vozlisca;

            vozlisca_v_robnem_pogoju.push_back(id_vozlisca);

        }

        vozlisca_robnih_pogojev.push_back(vozlisca_v_robnem_pogoju);

        std::string prazna_vrstica2;
        std::getline(file, prazna_vrstica2);
    }


// Tu je konec branja datoteke
    
//Sledeči blok kode nam preveri sosednjost vozlišč in to zapiše v obliki vektrojev

    double deltaX = 1.0;
    double deltaY = 1.0;
    double k = 1.0;

    vector<vector<int>> sosednja_vozlisca;
    
    for (int node_id = 0; node_id < n_vozlisc; node_id++) {
        vector<int> node_i_neighbours = { -1,-1,-1,-1 };

        for (int nd = 0; nd < n_celice; nd++) {
            vector<int> trenutna_celica = celice[nd];

            int vozlisce1 = trenutna_celica[0];
            int vozlisce2 = trenutna_celica[1];
            int vozlisce3 = trenutna_celica[2];
            int vozlisce4 = trenutna_celica[3];
            
            if (node_id == vozlisce1 || node_id == vozlisce2 || node_id == vozlisce3 || node_id == vozlisce4) {
                for (int vozl = 0; vozl < 4; vozl++) {

                    int sosednje_vozlisce = trenutna_celica[vozl];

                    int pozicija = 0;
                    
                    if (sosednje_vozlisce != node_id) {
                        double x_obravnavano_vozl = X[node_id];
                        double y_obravnavano_vozl = Y[node_id];

                        double x_sosed = X[sosednje_vozlisce];
                        double y_sosed = Y[sosednje_vozlisce];

                        
                        if ((x_obravnavano_vozl - x_sosed) < 1e-9 && (x_obravnavano_vozl - x_sosed) > -(1e-9)) {
                            if ((y_obravnavano_vozl - y_sosed) > 0.0) {
                                pozicija = 1;
                            }
                            else {
                                pozicija = 3;
                            }

                        }
                        
                        else if ((y_obravnavano_vozl - y_sosed) < 1e-9 && (y_obravnavano_vozl - y_sosed) > -(1e-9)) {
                            if ((x_obravnavano_vozl - x_sosed) > 0.0) {
                                pozicija = 0;
                            }
                            else {
                                pozicija = 2;
                            }

                        }
                        
                        else {
                            pozicija = -1;
                            
                        }
                        
                        if (pozicija != -1) {

                            node_i_neighbours[pozicija] = sosednje_vozlisce;

                        }

                    }
                    
                }

            }
            
        }
        sosednja_vozlisca.push_back(node_i_neighbours);
      
    }
    int n = n_vozlisc;
    
//Sledeči segment kode na podlagi prebranih podatkov in sosednjosti vozlišč sestavi matriko A in vektor b

    std::vector<std::vector<double>> A(n, std::vector<double>(n, 0.0));
    std::vector<double>b(n, 0.0);
    
    for (int node_id = 0; node_id < n_vozlisc; node_id++) {
        vector<int> sosedi = sosednja_vozlisca[node_id];
        int levi_sosed = sosedi[0];
        int spodnji_sosed = sosedi[1];
        int desni_sosed = sosedi[2];
        int zgornji_sosed = sosedi[3];
        
        if (levi_sosed != -1 && spodnji_sosed != -1 && desni_sosed != -1 && zgornji_sosed != -1) {
            A[node_id][levi_sosed] = 1.0;
            A[node_id][spodnji_sosed] = 1.0;
            A[node_id][desni_sosed] = 1.0;
            A[node_id][zgornji_sosed] = 1.0;
            A[node_id][node_id] = -4.0;
        }
        else {
            int tip_robnega_pogoja = 0;
            double vrednost=0;
            double vrednost_prestopa=0;

            for (int robni_pogoj_id = 0; robni_pogoj_id < n_pogoji; robni_pogoj_id++) {
                vector<int> vozlisca_v_trenutnem_rp = vozlisca_robnih_pogojev[robni_pogoj_id];

                for (int id_vozlisce_rp = 0; id_vozlisce_rp < vozlisca_v_trenutnem_rp.size(); id_vozlisce_rp++) {
                    int vozlisce_v_trenutnem_rp = vozlisca_v_trenutnem_rp[id_vozlisce_rp];

                    if (node_id == vozlisce_v_trenutnem_rp) {
                        tip_robnega_pogoja = tipi_robnih_pogojev[robni_pogoj_id];

                        vrednost = vrednosti_robnih_pogojev[robni_pogoj_id];

                        vrednost_prestopa = vrednosti_prestopa_toplote[robni_pogoj_id];
                    }

                }

            }

            if (tip_robnega_pogoja == 0) {
                A[node_id][node_id] = 1.0;
                b[node_id] = vrednost;
            }

            else if (tip_robnega_pogoja == 1) {
                int stevilo_sosedov = 0;

                for (int st = 0; st < 4; st++) {
                    if (sosedi[st] != -1) {
                        stevilo_sosedov = stevilo_sosedov + 1;
                    }
                }

                if (stevilo_sosedov == 3) {
                    if (levi_sosed == -1) {
                        A[node_id][node_id] = A[node_id][node_id] - 4.0;
                        A[node_id][desni_sosed] = A[node_id][desni_sosed] + 2.0;
                        A[node_id][spodnji_sosed] = A[node_id][spodnji_sosed] + 1.0;
                        A[node_id][zgornji_sosed] = A[node_id][zgornji_sosed] + 1.0;
                        b[node_id] = -2.0 * (vrednost * deltaX / k);
                    }
                    if (desni_sosed == -1) {
                        A[node_id][node_id] = A[node_id][node_id] - 4.0;
                        A[node_id][levi_sosed] = A[node_id][levi_sosed] + 2.0;
                        A[node_id][spodnji_sosed] = A[node_id][spodnji_sosed] + 1.0;
                        A[node_id][zgornji_sosed] = A[node_id][zgornji_sosed] + 1.0;
                        b[node_id] = -2.0 * (vrednost * deltaX / k);
                    }
                    if (spodnji_sosed == -1) {
                        A[node_id][node_id] = A[node_id][node_id] - 4.0;
                        A[node_id][spodnji_sosed] = A[node_id][spodnji_sosed] + 2.0;
                        A[node_id][levi_sosed] = A[node_id][levi_sosed] + 1.0;
                        A[node_id][desni_sosed] = A[node_id][desni_sosed] + 1.0;
                        b[node_id] = -2.0 * (vrednost * deltaX / k);
                    }
                }
            }

            else if (tip_robnega_pogoja == 2) {
                int stevilo_sosedov = 0;
                for (int st = 0; st < 4; st++) {
                    if (sosedi[st] != -1) {
                        stevilo_sosedov = stevilo_sosedov + 1;
                    }
                }

                if (stevilo_sosedov == 3) {
                    if (levi_sosed == -1) {
                        A[node_id][node_id] = A[node_id][node_id] - 2.0 * (vrednost_prestopa * deltaX / k + 2.0);
                        A[node_id][desni_sosed] = A[node_id][desni_sosed] + 2.0;
                        A[node_id][spodnji_sosed] = A[node_id][spodnji_sosed] + 1.0;
                        A[node_id][zgornji_sosed] = A[node_id][zgornji_sosed] + 1.0;
                        b[node_id] = b[node_id] - (2.0 * vrednost_prestopa * deltaX * vrednost / k);
                    }

                    if (desni_sosed == -1) {
                        A[node_id][node_id] = A[node_id][node_id] - 2.0 * (vrednost_prestopa * deltaX / k + 2.0);
                        A[node_id][levi_sosed] = A[node_id][levi_sosed] + 2.0;
                        A[node_id][spodnji_sosed] = A[node_id][spodnji_sosed] + 1.0;
                        A[node_id][zgornji_sosed] = A[node_id][zgornji_sosed] + 1.0;
                        b[node_id] = b[node_id] - 2.0 * vrednost_prestopa * deltaX * vrednost / k;
                    }

                    if (spodnji_sosed == -1) {
                        A[node_id][node_id] = A[node_id][node_id] - 2.0 * (vrednost_prestopa * deltaX / k + 2.0);
                        A[node_id][levi_sosed] = A[node_id][levi_sosed] + 1.0;
                        A[node_id][desni_sosed] = A[node_id][desni_sosed] + 1.0;
                        A[node_id][zgornji_sosed] = A[node_id][zgornji_sosed] + 2.0;
                        b[node_id] = -2.0 * vrednost_prestopa * deltaX * vrednost / k;
                    }

                    if (zgornji_sosed == -1) {
                        A[node_id][node_id] = A[node_id][node_id] - 2.0 * (vrednost_prestopa * deltaX / k + 2.0);
                        A[node_id][levi_sosed] = A[node_id][levi_sosed] + 1.0;
                        A[node_id][desni_sosed] = A[node_id][desni_sosed] + 1.0;
                        A[node_id][spodnji_sosed] = A[node_id][spodnji_sosed] + 2.0;
                        b[node_id] = -2.0 * vrednost_prestopa * deltaX * vrednost / k;
                    }
                }
            }
        }
    }

//Sedaj imamo matriko A in vektor b. jupi

//Shranjevanje matrike A in vektorja b za uporabo v MATLABu.

    std::ofstream fileIDA;
    fileIDA.open("A.csv");

    for (int i = 0; i < A[0].size(); i++)
    {

        fileIDA << A[i][0];

        for (int j = 1; j < A[0].size(); j++)
        {
            fileIDA << ", " << A[i][j];
        }

        fileIDA << endl;
    }
    fileIDA.close();

    std::ofstream fileIDb;
    fileIDb.open("b.csv");

    for (int i = 0; i < b.size(); i++)
    {
        fileIDb << b[i] << ", ";

        fileIDb << endl;
    }
    fileIDb.close();

//Začetek merjenja časa računanja sistema enačb
    auto start_time = std::chrono::high_resolution_clock::now();

//Računanje sistema enačb z Gauss-Seidlovo metodo

    vector<double> T;
    for (int iiT = 0; iiT < n; iiT++)
    {
        T.push_back(100);
    }

    for (int ii = 0; ii < 2000; ii++)
    {
        for (int jj = 0; jj < n; jj++) {
            double d = b[jj];
            for (int ii = 0; ii < n; ii++) {
                if (jj != ii) {
                    d = d - A[jj][ii] * T[ii];
                }
            }
            T[jj] = d / A[jj][jj];
        }

    }
    
    auto end_time = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> time_duration = end_time - start_time;
    std::cout << "Cas Gauss-Seidl metode: " << time_duration.count() << " sekund" << std::endl;

//Tu je sicer še možnost da program izpiše vrednosti temperature v vsakemu vozslišču in izračuna ter izpiše max. temperaturo, kot v DN5.
//Da tega ne izpisuje vsakič je v tem dukumentu ta del kode zakomentiran.

    /*
    double max_T = 0;
    for (int iiT = 0; iiT < n; iiT++)
    {
        cout << T[iiT] << endl;

        if (T[iiT] > max_T) {
            max_T = T[iiT];
        }
    }
    std::cout << "Max. temperature: " << max_T << " degree C." << endl;
    */

    //Zapis rezultatov v .vtk datoteki

    std::ofstream fileID;
    fileID.open("rezultat_vtkcpp.vtk");

    fileID << "# vtk DataFile Version 3.0\n";
    fileID << "Mesh_1\n";
    fileID << "ASCII\n";
    fileID << "DATASET UNSTRUCTURED_GRID\n";
    fileID << "POINTS " << n_vozlisc << " float\n";
    for (int koordinata_id = 0; koordinata_id < n_vozlisc; koordinata_id++) {
        fileID << X[koordinata_id] << " " << Y[koordinata_id] << " 0\n";
    }
    fileID << "\n";
    fileID << "CELLS " << n_celice << " " << n_celice * 5 << "\n";
    for (int celica_id = 0; celica_id < n_celice; celica_id++) {
        int vozl_id1 = celice[celica_id][0];
        int vozl_id2 = celice[celica_id][1];
        int vozl_id3 = celice[celica_id][2];
        int vozl_id4 = celice[celica_id][3];
        fileID << "4 " << vozl_id1 << " " << vozl_id2 << " " << vozl_id3 << " " << vozl_id4 << "\n";
    }
    fileID << "\n";
    fileID << "CELL_TYPES " << n_celice << "\n";
    for (int celica_id = 0; celica_id < n_celice; celica_id++) {
        fileID << "9\n";
    }
    fileID << "\n";
    fileID << "POINT_DATA " << n_vozlisc << "\n";
    fileID << "SCALARS Temperature float 1\n";
    fileID << "LOOKUP_TABLE default\n";
    for (int koordinata_id = 0; koordinata_id < n_vozlisc; koordinata_id++) {
        fileID << T[koordinata_id] << "\n";
    }

    fileID.close();
    

    std::cout << "Hello World!\n";
}

    fileID.close();

    std::cout << "Hello World!\n";
}
