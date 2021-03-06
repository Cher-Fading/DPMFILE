//name format /sphenix/user/xwang97/DPMJET/$A/fort_$A_$2_1E2.root
bool filenameparser(std::string filename, int &jobnum, std::string &evtnb, std::string &jobname)
{
    //initialize the values
    //condorbatch = -1;
    jobnum = -1;
    evtnb = "";
    jobname = "";
    //cout << filename << endl;

    TString fileName = filename.data();
    int ending = filename.find(".root");
    if (ending == std::string::npos)
    {
        cout << "[ERROR] Wrong name, can't find .root: " << filename << endl;
        return false;
    }

    /*int En = filename.rfind("E", ending - 1);
    std::string Es = filename.substr(En + 1, ending - En - 1);
    int E = std::stoi(Es);
    if (!(E >= 0))
    {
        cout << "[ERROR] Wrong power: " << Es << endl;
        return false;
    }

    
    std::string Eds = filename.substr(last_ + 1, En - last_ - 1);
    int Ed = std::stoi(Eds);
    if (!(Ed >= 0))
    {
        cout << "[ERROR] Wrong digit: " << Eds << endl;
        return false;
    }
    evtnb = Ed * pow(10, E);
    if (!(evtnb >= 0))
    {
        cout << "[ERROR] Wrong event number: " << Eds << "*" << Es << endl;
        return false;
    }*/
    int last_ = filename.rfind("_", ending - 1);
    evtnb=filename.substr(last_+1,ending-last_-1);
    

    int seclast_ = filename.rfind("_", last_ - 1);
    std::string jobnums = filename.substr(seclast_ + 1, last_ - seclast_ - 1);
    jobnum = std::stoi(jobnums);
    if (!(jobnum >= 0))
    {
        cout << "[ERROR] Wrong jobnum: " << jobnums << endl;
        return false;
    }

    /*int thirdlast_ = filename.rfind("_", seclast_ - 1);
    std::string condorbatchs = filename.substr(thirdlast_ + 1, seclast_ - thirdlast_-1);
    condorbatch = std::stoi(condorbatchs);
    if (!(condorbatch >= 0))
    {
        cout << "[ERROR] Wrong condorbatch: " << condorbatchs << endl;
        return false;
    }*/

    int fort_ = filename.rfind("fort_", seclast_-1);
    jobname =filename.substr(fort_+5,seclast_-fort_-5);

    
    return true;
}
