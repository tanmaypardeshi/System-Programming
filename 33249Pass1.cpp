#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

static int literalPoolCount=0;
static int locationCounter;

vector<string>literalVec;
vector<int>literalsLC;
vector<int>literalPool;

vector<string>symbolVec;
vector<int>symbolLC;

typedef struct operand1
{
    string operand1;
    char type;
    int code;

}operand1Code;

typedef struct motValuesStructure
{
    string opcode;
    string size;
    string type;
    string noOfOperands;
}motValues;

auto getmneOpcodeType(string mne,int labelFlag=0)
{   
    tuple<string,string>tyepOpcodeTuple;
    map<string,motValues>mneMap;
    int count=0,i=0;
    fstream mneFile;
    mneFile.open("/home/harsh/Downloads/input3.txt",ios::in);
    string motKeys[18];
    motValues arrOfValues[18];

    if(mneFile.is_open())
    {
        string temp;
        while(getline(mneFile,temp))
        {
            
            char tempCharArray[200];

            strcpy(tempCharArray,temp.c_str());
            
            char *token;
            char *rest=tempCharArray;

            token= strtok_r(rest,"\t",&rest);
            motKeys[count]=token;

            token= strtok_r(rest,"\t",&rest);
            arrOfValues[count].opcode=token;

            token= strtok_r(rest,"\t",&rest);
            arrOfValues[count].size=token;

            token= strtok_r(rest,"\t",&rest);
            arrOfValues[count].type=token;

            token= strtok_r(rest,"\t",&rest);
            arrOfValues[count].noOfOperands=token;
            
            count++;
        }
        
    }
    mneFile.close();

    for(i=0;i<18;i++)
    {
        mneMap[motKeys[i]]=arrOfValues[i];
    }

    if(labelFlag==1)
    {
        symbolLC.push_back(locationCounter);
    }

    locationCounter+=std::atoi((mneMap[mne].size).c_str());

    get<0>(tyepOpcodeTuple)=mneMap[mne].type;
    get<1>(tyepOpcodeTuple)=mneMap[mne].opcode;


    return tyepOpcodeTuple;

}


auto getOperand1TypeCode(string op1)
{
    tuple<char,int> operand1Tuple;
    int i=0;
    map<string,pair<char,int>>operand1Map;

    operand1Code values[11]={
        {"AREG",'r',1},
        {"BREG",'r',2},
        {"CREG",'r',3},
        {"DREG",'r',4},
        {"LT",'c',1},
        {"LE",'c',2},
        {"GT",'c',3},
        {"GE",'c',4},
        {"EQ",'c',5},
        {"NE",'c',6},
        {"ANY",'c',7}
    };

    for(i=0;i<11;i++)
    {
        operand1Map.insert( std::make_pair((values[i].operand1), (std::make_pair(values[i].type,values[i].code))));   
    }

    get<0>(operand1Tuple)=operand1Map[op1].first;
    get<1>(operand1Tuple)=operand1Map[op1].second;

    return operand1Tuple;

}


char checkOperand2Type(string op2)
{
    if(op2.at(0) == '=')
    {
        return 'L';
    }

    else if(isalpha(op2[0])!=0)
    {
        return 'S';
    }

    //else if(op2[0]=='-')
    //{
        //return '-';
    //}
    else
    {
        return 'C';
    }

}


int main()
{
    int index;
    int existsFlag=0;
    literalPool.push_back(0);
    tuple<string,string>mneTypeOpcodeTuple;
    tuple<char,int> operand1Tuple;

    int i,count=0;
    fstream asmFile;

    asmFile.open("/home/harsh/TE_Pracs_Sem2/SL5/SP/Hashing/asmTest2.txt",ios::in);

    int lineNo=0;
    if(asmFile.is_open())
    {
        string temp;
        while(getline(asmFile,temp))
        {
            if((temp.find("LTORG")!=std::string::npos) || (temp.find("END")!=std::string::npos))
            {
                cout<<"-";
                mneTypeOpcodeTuple=getmneOpcodeType(temp,0);
                cout<<"("<<get<0>(mneTypeOpcodeTuple)<<","<<get<1>(mneTypeOpcodeTuple)<<")"; 
                cout<<"-";
                cout<<"-";
                literalPool.push_back(literalVec.size());
                for(int i=0;i<literalVec.size();i++)
                {
                    literalsLC.push_back(locationCounter);
                    locationCounter++;
                }
    
            }
            else if((temp.find("DC")!=std::string::npos) || (temp.find("DS")!=std::string::npos))
            {
                char tempCharArray[200];
                strcpy(tempCharArray,temp.c_str());

                char *token;
                char *rest=tempCharArray;

                token=strtok_r(rest,"\t",&rest);
                string label=token;

                token=strtok_r(rest,"\t",&rest);
                string mne=token;

                token=strtok_r(rest,"\t",&rest);
                string op1=token;

                token=strtok_r(rest,"\t",&rest);
                string op2=token;

                if(label=="-")
                {
                    cout<<"-";
                }
                else
                {   
                    if(find(symbolVec.begin(),symbolVec.end(),label)==symbolVec.end())
                    {
                        existsFlag=0;
                        symbolVec.push_back(label);
                        auto it=find(symbolVec.begin(),symbolVec.end(),label);
                        int index=it-symbolVec.begin();
                        cout<<"(S,"<<index<<")";
                    }
                    else
                    {   
                        existsFlag=1;
                        auto it=find(symbolVec.begin(),symbolVec.end(),label);
                        int index=it-symbolVec.begin();
                        cout<<"(S,"<<index<<")";
                    }
                    
                }

                if(existsFlag==0)
                {
                    mneTypeOpcodeTuple=getmneOpcodeType(mne,1);
                }
                else
                {
                    mneTypeOpcodeTuple=getmneOpcodeType(mne,0);
                }
                cout<<"("<<get<0>(mneTypeOpcodeTuple)<<","<<get<1>(mneTypeOpcodeTuple)<<")";                 

                if(op1=="-")
                {
                    cout<<"-";
                }
                else
                {
                    operand1Tuple=getOperand1TypeCode(op1);
                    cout<<"("<<get<0>(operand1Tuple)<<","<<get<1>(operand1Tuple)<<")";                                        
                }

                
                cout<<"(C,"<<op2<<")";

            }

            else if(temp.find("EQU")!=std::string::npos)
            {   
                char tempCharArray[200];
                strcpy(tempCharArray,temp.c_str());

                char *token;
                char *rest=tempCharArray;

                token=strtok_r(rest,"\t",&rest);
                string label=token;

                token=strtok_r(rest,"\t",&rest);
                string mne=token;

                token=strtok_r(rest,"\t",&rest);
                string op1=token;

                token=strtok_r(rest,"\t",&rest);
                string op2=token;

                if(label=="-")
                {
                    cout<<"-";
                }

                else
                {
                    auto it=find(symbolVec.begin(),symbolVec.end(),label);
                    index=it-symbolVec.begin();   
                    cout<<"(L,"<<index<<")";                 
                }

                if(mne=="-")
                {
                    cout<<"-";
                }
                else
                {
                    mneTypeOpcodeTuple=getmneOpcodeType(mne,0);
                    cout<<"("<<get<0>(mneTypeOpcodeTuple)<<","<<get<1>(mneTypeOpcodeTuple)<<")";   
                }

                cout<<"-";

                auto it1=find(symbolVec.begin(),symbolVec.end(),op2);
                int index1=it1-symbolVec.begin();                
                symbolLC[index]=symbolLC[index1];

                cout<<"(S,"<<index1<<")";
                
            }
            
            else
            {
                char tempCharArray[200];
                strcpy(tempCharArray,temp.c_str());

                char *token;
                char *rest=tempCharArray;

                token=strtok_r(rest,"\t",&rest);
                string label=token;

                token=strtok_r(rest,"\t",&rest);
                string mne=token;

                token=strtok_r(rest,"\t",&rest);
                string op1=token;

                token=strtok_r(rest,"\t",&rest);
                string op2=token;

                if(label=="-")
                {
                    cout<<"-";
                }

                else
                {
                    auto it=find(symbolVec.begin(),symbolVec.end(),label);
                    int index;
                    index=it-symbolVec.begin();
                    symbolLC[index]=locationCounter;
                    cout<<"(S,"<<index<<")";
                    //symbolVec.push_back(label);                    
                }


                if(mne=="-")
                {
                    cout<<"-";
                }

                else if(mne=="START")
                {
                    locationCounter=std::atoi(op2.c_str());

                    mneTypeOpcodeTuple=getmneOpcodeType(mne,0);
                    cout<<"("<<get<0>(mneTypeOpcodeTuple)<<","<<get<1>(mneTypeOpcodeTuple)<<")";                   
                }

                else
                {
                    if(checkOperand2Type(op2)=='S')
                    {
                        symbolLC.push_back(-1);    
                    }
                    else
                    {
                        mneTypeOpcodeTuple=getmneOpcodeType(mne,0);   
                    }
                    cout<<"("<<get<0>(mneTypeOpcodeTuple)<<","<<get<1>(mneTypeOpcodeTuple)<<")";                    
                }


                if(op1=="-")
                {
                    cout<<"-";
                }

                else
                {
                    operand1Tuple=getOperand1TypeCode(op1);
                    cout<<"("<<get<0>(operand1Tuple)<<","<<get<1>(operand1Tuple)<<")";                    
                }


                if(op2=="-")
                {
                    cout<<"-";
                }         

                if(checkOperand2Type(op2)=='L')
                {
                    int index;
                    literalVec.push_back(op2);
                    int tracker=literalPool[literalPool.size()-1];
                    auto it=find(literalVec.begin()+tracker,literalVec.end(),op2);
                    index=it-literalVec.begin();
                    cout<<"(L,"<<index<<")";
                }

                else if(checkOperand2Type(op2)=='C')
                {
                    cout<<"(C,"<<op2<<")";
                }

                else
                {
                    //label condition
                    symbolVec.push_back(op2);
                    auto it=find(symbolVec.begin(),symbolVec.end(),op2);
                    int index;
                    index=it-symbolVec.begin();
                    //symbolLC[index]=locationCounter;
                    cout<<"(S,"<<index<<")";                    
                }
                
            }

            cout<<endl;
        }

    }
    asmFile.close();

    cout<<endl<<endl;
    cout<<"Literal Table:-"<<endl;

    for(int i=0;i<literalVec.size();i++)
    {
        cout<<literalVec[i]<<" "<<literalsLC[i]<<endl;
    }

    cout<<endl;
    cout<<"Literal Pool:-"<<endl;

    for(int i=0;i<literalPool.size();i++)
    {
        cout<<literalPool[i]<<endl;
    }

    cout<<endl<<endl;

    cout<<"Symbol Table:-"<<endl;

    for(int i=0;i<symbolVec.size();i++)
    {
        cout<<symbolVec[i]<<" "<<symbolLC[i]<<endl;
    }
}


/*

Input:-
-	START	-	1000
-	MOVER	AREG	='1'
-	BC	LT	XYZ
A	DC	-	01
-	DIV	AREG	='2'
XYZ	ADD	DREG	='3'
LTORG
-	DIV	CREG	='1'
-	MOVEM	AREG	='2'
LTORG
-	STOP	-	-
A	DC	-	10
B	DS	-	10
A	EQU	-	B
END


Output:-
(base) harsh@harsh-Inspiron-7570:~/TE_Pracs_Sem2/SL5/SP/Hashing$ g++ 33249Pass1.cpp
(base) harsh@harsh-Inspiron-7570:~/TE_Pracs_Sem2/SL5/SP/Hashing$ ./a.out
-(AD,01)-(C,1000)
-(IS,04)(r,1)(L,0)
-(IS,04)(c,1)(S,0)
(S,1)(DL,01)-(C,01)
-(IS,08)(r,1)(L,1)
(S,0)(IS,01)(r,4)(L,2)
-(AD,03)--
-(IS,08)(r,3)(L,3)
-(IS,05)(r,1)(L,4)
-(AD,03)--
-(IS,00)--(C,-)
(S,1)(DL,01)-(C,10)
(S,2)(DL,02)-(C,10)
(L,1)(AD,05)-(S,2)
-(AD,04)--


Literal Table:-
='1' 1008
='2' 1009
='3' 1010
='1' 1017
='2' 1018

Literal Pool:-
0
3
5
5


Symbol Table:-
XYZ 1006
A 1024
B 1024
(base) harsh@harsh-Inspiron-7570:~/TE_Pracs_Sem2/SL5/SP/Hashing$ 

