#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#ifdef __CLING__
// these are not headers - do not treat them as such - needed for ROOT6
#include "filenameparser.cpp"
#endif

#ifdef __CINT__
gROOT->LoadMacro("filenameparser.cpp");
#endif

void countmissedread(std::string list1 = "ep_HERA4"){//2 for single batch and 3 for multi-batch


int done[200];
int full[200];
    std::ifstream froot(Form("/sphenix/xwang97/DPMJEt/%s/%s_readfiles.txt",list1.c_str(),list1.c_str()));
    //std::ifstream fdone(Form("../GetStuff/%s_countsdone%s.txt", dataType.c_str(), suffix[pnfs]));
    //std::ofstream fmiss(Form("../GetStuff/%s_countsmiss%s.txt", dataType.c_str(), suffix[pnfs]));

    std::ifstream fdone(Form("../GetStuff/%s%s_donesmall%s.txt", dataType.c_str(), Type[PbPb], suffix[pnfs]));
    std::ofstream fmiss(Form("../GetStuff/%s%s_misssmall%s.txt", dataType.c_str(), Type[PbPb], suffix[pnfs]));

    int cent_N = PbPb ? cet_N : 1;
    cout << "centrality: " << cent_N << endl;
    int totf = 0;
    int donef[cent_N];
    int outf[cent_N];
    for (int c = 0; c < cent_N; c++)
    {
        donef[c] = 0;
        outf[c] = 0;
    }


    for (int i = 0; i < gridsize; i++)
    {
        for (int j = 0; j < 3000; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                full[i][j][k] = 0;
                for (int c = 0; c < cent_N; c++)
                {
                    done[i][j][k][c] = 0;
                }
            }
        }
    }

    std::string line0;
    std::string linec;
    int shift = 5;
    while (getline(fdone, line0))
    {
        if (line0.find("_") == std::string::npos)
            continue;
        //cout << line0 << endl;
        //cout << line0.substr(5-shift, 1) << endl;
        /*std::ifstream fc(Form("/atlasgpfs01/usatlas/data/cher97/%s%s_Counts%s/%s", dataType.c_str(), Type[PbPb], suffix[pnfs], line0.c_str()));
	bool empty = false;
        while (getline(fc, linec))
        {
            if (linec.find("Light Total") == std::string::npos)
                continue;
	    int count = std::stoi(linec.substr(linec.rfind(" ") + 1, linec.length()-linec.rfind(" ") - 1));
	    //cout << count << endl;
	    //cout << line0 << endl;
	    //return;
            if (count == 0)
                empty = true;
        }
        fc.close();
	if (empty) continue;*/
        JZ = std::stoi(line0.substr(5 - shift, 1));
        //cout << line0.substr(7-shift, 1) << endl;
        tag = std::stoi(line0.substr(7 - shift, 1));
        int cet_length = PbPb ? 2 : 0;
        //cout << line0.substr(9-shift, line0.length() - (20-shift) - cet_length) << endl;
        NUM = std::stoi(line0.substr(9 - shift, line0.length() - (20 - shift) - cet_length));
        //cout << line0.substr(line0.length() - 12, 1) << endl;
        int central = PbPb ? std::stoi(line0.substr(line0.length() - 12, 1)) : 0;
        //if (line0=="100k_5_0_1323_counts.txt") cout << JZ << tag << NUM << central << endl;
        done[JZ][NUM][tag][central] = 1;
        //if (line0=="100k_5_0_1323_counts.txt") cout << done[JZ][NUM][tag][central] << endl;
        donef[central]++;
        //return;
        //delete fc;
        //return;
    }

    std::string line;
    while (getline(froot, line))
    {
        bool parsed = parse_filename_short(line, dataType, PbPb, pnfs, inclusive, JZ, tag, NUM, true);
        //cout << line << endl;
        //cout << "JZ" << JZ << "tag" << tag << "NUM" << NUM << endl;
        if (!parsed)
        {
            cout << "[ERROR]: parsing failed" << endl;
            return;
        }
        if (full[JZ][NUM][tag] == 1)
        {
            cout << "name repeated for full at JZ: " << JZ << "; NUM: " << NUM << "; tag: " << tag << endl;
            return;
        }
        full[JZ][NUM][tag] = 1;
        totf++;
        bool missing = false;
        for (int c = 0; c < cent_N; c++)
        {
            //cout << done[JZ][NUM][tag][c] << endl;
            if (done[JZ][NUM][tag][c] != 1)
            {
                missing = true;
                //cout << line << " for centrality: " << c << endl;
                outf[c]++;
            }
        }
        if (missing)
            fmiss << line << endl;
        //fmiss << JZ << "_" << tag << "_" << NUM << "_small.root" << endl;
        //return;
    }

    /*for (int i = 0; i < gridsize; i++)
    {
        for (int j = 0; j < 3000; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                for (int c = 0; c < cent_N; c++)
                {
                    if (done[i][j][k][c] == 1 && full[i][j][k] != 1)
                    {
                        cout << "JZ: " << i << endl;
                        cout << "ID: " << j << endl;
                        cout << "tag: " << k << endl;
                        std::string C = PbPb ? std::to_string(c) : "pp";
                        cout << "centrality: " << C << endl;
                    }
                }
            }
        }
    }*/

    cout << totf << endl;
    for (int c = 0; c < cent_N; c++)
    {
        cout << "done: centrality: " << c << ": " << donef[c] << endl;
        cout << "rerun: centrality: " << c << ": " << outf[c] << endl;
    }
    fmiss.close();
    fdone.close();
    froot.close();
}
}