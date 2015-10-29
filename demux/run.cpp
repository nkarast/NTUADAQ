#include <iostream>
#include <fstream>
#include <arpa/inet.h>
#include <stdint.h>
#include <map>
#include <cstring>
#include <stdlib.h>


 #include <TCanvas.h>
 #include <TH1.h>
 #include <TROOT.h>
 #include <TFile.h>


#define debug 1
#define OLD_DATA_FORMAT 1

using namespace std;

int endian (int i){
    unsigned char b1, b2, b3, b4;
    b1 = i & 255;
    b2 = ( i >> 8 ) & 255;
    b3 = ( i >> 16 ) & 255;
    b4 = ( i >> 24 ) & 255;
    
    return ((unsigned int)b1 << 24) + ((unsigned int)b2 << 16) + ((unsigned int)b3 << 8) + b4;
}

void demux(uint32_t dataWord, int &chNumber, int &chData){
    chNumber 	= (dataWord & 0x7FF000) >> 12;
    chData  	= (dataWord & 0xFFF);
}

int run(){//main(){
    ifstream input("../run9005.dat", ios::in|ios::binary);
    
    uint32_t temp;
    
    ifstream mapping("../inputFiles/Mapping.txt", ios::in);
    map<int, int> chMap;
    
    string tmp[96][2];
    int mapIntArray[96][2];
    for(int i=0; i<96; i++){
        for(int j=0; j<2; j++){
            mapping >> tmp[i][j];
            mapIntArray[i][j] = atoi(tmp[i][j].c_str());
        }
        chMap[i]=mapIntArray[i][1];
    }
    
    if(debug){
        for(int i=0; i<96; i++){
            cout << "i=" << i << "\t map["<<i<<"]=" <<chMap[i] << endl;
        }
    }
    
    //return 0;
    
    
    //if(debug) ofstream output("output.dat", ios::out|ios::binary);
    
    union{
        int32_t hex;
        int integer;
        char bytes[4];
    }repres;
    
    int runNumber;
    int date;
    int time;
    int type;
    
    int evNumber;
    int evStartTime;
    int evCramID;
    int evFIFOID;
    int evNumOfWordsRead;
    
    int runTotalEvents;
    int runEndDate;
    int runEndTime;
    
    
    TH1F *hitmap[4];
    hitmap[0] = new TH1F("hitmap_0", "hitmap_0", 96, 0, 96);
    hitmap[1] = new TH1F("hitmap_1", "hitmap_1", 96, 0, 96);
    hitmap[2] = new TH1F("hitmap_2", "hitmap_2", 96, 0, 96);
    hitmap[3] = new TH1F("hitmap_3", "hitmap_3", 96, 0, 96);
    
    
    TH1F *noMap[4];
    noMap[0] = new TH1F("noMap_0", "noMap_0", 96, 0, 96);
    noMap[1] = new TH1F("noMap_1", "noMap_1", 96, 0, 96);
    noMap[2] = new TH1F("noMap_2", "noMap_2", 96, 0, 96);
    noMap[3] = new TH1F("noMap_3", "noMap_3", 96, 0, 96);
    
    int n=0;
    while(!input.eof()){
        input.read((char*) &temp, sizeof(uint32_t));
        
        if(debug) cout << hex << endian(temp) << dec <<  endl;
        
        
        if(endian(temp) == 0x90000000){
            input.read((char*) &temp, sizeof(uint32_t));
            runNumber=endian(temp);
            if(debug) cout << "RunNumber " << runNumber << endl;
            
            input.read((char*) &temp, sizeof(uint32_t));
            date=endian(temp);
            if(debug) cout << "date " << date << endl;
            
            input.read((char*) &temp, sizeof(uint32_t));
            time=endian(temp);
            if(debug) cout << "time " << time << endl;
            
            input.read((char*) &temp, sizeof(uint32_t));
            type=endian(temp);
            if(debug) cout << "type " << type << endl;
        }
        else if(endian(temp) == 0x9ffff000){
            if(debug) 	cout << "Header End found!" << endl;
            continue;
            //	break;
        }
        else if(endian(temp) == 0x80000000){
            if(debug) cout << "NEW EVENT!!" << endl;
            input.read((char*) &temp, sizeof(uint32_t));
            evNumber = endian(temp);
            if(debug) cout << "evNumber " << evNumber << endl;
            
            input.read((char*) &temp, sizeof(uint32_t));
            evStartTime = endian(temp);
            if(debug) cout << "evStartTime " << evStartTime << endl;
            
            for(int i=0; i<4; i++){
                input.read((char*) &temp, sizeof(uint32_t));
                evCramID = endian(temp);
                if(debug) cout << "evCramID " << evCramID << endl;
                
                if(OLD_DATA_FORMAT){
                    input.read((char*) &temp, sizeof(uint32_t));
                    evFIFOID = endian(temp);
                    if(debug) cout << "evFIFOID " << evFIFOID << endl;
                }
                
                
                input.read((char*) &temp, sizeof(uint32_t));
                evNumOfWordsRead = endian(temp);
                if(debug) cout << "evNumOfWordsRead " << evNumOfWordsRead << endl;
                
                for(int k=0; k<evNumOfWordsRead; k++){
                    uint32_t dataVector[evNumOfWordsRead];
                    //int32_t dataVector[evNumOfWordsRead];
                    input.read((char*) &temp, sizeof(uint32_t));
                    dataVector[k]=endian(temp);
                    int chNumber, chData;
                    demux(dataVector[k], chNumber,chData);
                    if(debug) cout << "dataVector[" << k << "] = " << dataVector[k] << "ChNum: " << chNumber << "\t ChData: " << chData << endl;
                    if(chData==1023){
                        hitmap[i]->Fill(chMap[chNumber], 0);
                        noMap[i]->Fill(chNumber, 0);
                    }
                    else{
                        hitmap[i]->Fill(chMap[chNumber], chData);
                        noMap[i]->Fill(chNumber, chData);
                        //cout<<chNumber<<" , "<<chMap[chNumber]<<" , "<< chData <<endl;
                    }
                }
                
                if(debug) cout << "i is " << i << endl;
            }
            //break;
            continue;
        }//if temp = EVENT BEGIN
        else if(endian(temp) == 0x8ffff000){
            if(debug) cout << "EVENT END!!" << endl;
            continue;
        }
        else if(endian(temp) == 0xa0000000){
            if(debug) cout << "STARTING FOOTER!!!" << endl;
            if(debug) cout << "############################################### \n ###############################################" << endl;
            input.read((char*) &temp, sizeof(uint32_t));
            runTotalEvents = endian(temp);
            if(debug) cout << "Total Events in Run = " << runTotalEvents << endl;
            
            input.read((char*) &temp, sizeof(uint32_t));
            runEndDate = endian(temp);
            if(debug) cout << "Run End Date = " << runEndDate << endl;
            
            input.read((char*) &temp, sizeof(uint32_t));
            runEndTime = endian(temp);
            if(debug) cout << "Run End Time = " << runEndTime << endl;
            
            continue;
        }//else trailer begin
        else if(endian(temp) == 0xaffff000){
            if(debug) cout << " $$$$$ FILE ENDED $$$$$$ " << endl;
            break;
        }//if trailer end
        
        //~ cout << "n is " << n << endl;
        //~ n++;
        //n++;
        
        //input.read((char*) &temp, sizeof(uint32_t));
        //cout << "temp " << hex << endian(temp) <<  dec << endian(temp) <<endl;
        
    }
    
    cout << "FILE CLOSED. PROCESSED " << evNumber << " EVENTS. " << endl;
    input.close();
    
    TFile *outfile = new TFile("9005_processed.root", "recreate");
    outfile->cd();
    hitmap[0]->Write();
    hitmap[1]->Write();
    hitmap[2]->Write();
    hitmap[3]->Write();
    outfile->Close();
    
    
    /*
     TCanvas *c1 = new TCanvas();
     c1->Divide(2,2);
     c1->cd(1);
     hitmap[0]->Draw();
     c1->cd(2);
     hitmap[1]->Draw();
     c1->cd(3);
     hitmap[2]->Draw();
     c1->cd(4);
     hitmap[3]->Draw();
     
     TCanvas *c11 = new TCanvas();
     c11->Divide(2,2);
     c11->cd(1);
     noMap[0]->Draw();
     c11->cd(2);
     noMap[1]->Draw();
     c11->cd(3);
     noMap[2]->Draw();
     c11->cd(4);
     noMap[3]->Draw();
     
     c1->SaveAs("Zabarakatranemia_Ileos_Ileos3.gif");
     c11->SaveAs("proMap3.gif");
     */
    //output.close();
    return 0;
}
