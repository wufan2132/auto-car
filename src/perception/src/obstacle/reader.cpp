#include "perception/reader.h"


reader::reader(string path,string io){
     if(io=="read"){
        mode =1;
        save_path = path;
        inFile.open(save_path.c_str(), ios::in); // 打开模式可省略
        char cwd[50];
        getcwd(cwd,sizeof(cwd));
        cout<<"inFile open:"<<cwd<<endl;
    }else if(io=="write"){
        mode = 2;
        save_path = path;
        outFile.open(save_path.c_str(), ios::out); // 打开模式可省略
        char cwd[50];
        getcwd(cwd,sizeof(cwd));
        cout<<"outFile open:"<<cwd<<endl;
    }else
        mode=0;
};

reader::~reader(){
    if(mode==1)
        inFile.close();
    else if(mode==2)
        outFile.close();
}

void reader::readinit(string path){
        if(mode==0){
            mode =1;
            save_path = path;
            inFile.open(save_path.c_str(), ios::in); // 打开模式可省略
            char cwd[50];
            getcwd(cwd,sizeof(cwd));
            cout<<"inFile open:"<<cwd<<endl;
        }
}
void reader::writeinit(string path){
        if(mode==0){
            mode = 2;
            save_path = path;
            outFile.open(save_path.c_str(), ios::out); // 打开模式可省略
            char cwd[50];
            getcwd(cwd,sizeof(cwd));
            cout<<"outFile open:"<<cwd<<endl;
        }
}

void reader::reset(){
    if(mode==1){
        inFile.clear();
        inFile.seekg(0,ios::beg);
    }
    else if(mode==2){
        outFile.seekp(0,ios::beg);
    }
}

void reader::close(){
    if(mode==1)
        inFile.close();
    else if(mode==2)
        outFile.close();
    mode = 0;
}


bool reader::readOnce(car_msgs::base_obstacle& object){
    static int count = 0;
    if(mode!=1) 
    {
        cout<<"mode err!";
        return 0;
    }
    string lineStr;
    getline(inFile, lineStr);
    if(lineStr.size()<10)
    {
        count = 0;
        return 0;
    }
        
    stringstream ss(lineStr);
	string str;
    object.header.seq = count;
    object.xa.resize(4);
    object.ya.resize(4);
    object.theta_a.resize(4);

    getline(ss, str, ',');
    object.type=atoi(str.c_str());

    getline(ss, str, ',');
    object.xa[0]=atof(str.c_str());
    getline(ss, str, ',');
    object.xa[1]=atof(str.c_str());
    getline(ss, str, ',');
    object.xa[2]=atof(str.c_str());
    getline(ss, str, ',');
    object.xa[3]=atof(str.c_str());

    getline(ss, str, ',');
    object.ya[0]=atof(str.c_str());
    getline(ss, str, ',');
    object.ya[1]=atof(str.c_str());
    getline(ss, str, ',');
    object.ya[2]=atof(str.c_str());
    getline(ss, str, ',');
    object.ya[3]=atof(str.c_str());

    getline(ss, str, ',');
    object.theta_a[0]=atof(str.c_str());
    getline(ss, str, ',');
    object.theta_a[1]=atof(str.c_str());
    getline(ss, str, ',');
    object.theta_a[2]=atof(str.c_str());
    getline(ss, str, ',');
    object.theta_a[3]=atof(str.c_str());

    getline(ss, str, ',');
    object.a=atof(str.c_str());
    getline(ss, str, ',');
    object.b=atof(str.c_str());

    count++;
    return 1;
}


/*


//
bool reader::readOnce(car_msgs::trajectory_point &point){
    static int count = 0;
    if(mode!=1) 
    {
        cout<<"mode err!";
        return 0;
    }
    string lineStr;
    getline(inFile, lineStr);
    if(lineStr.size()<10)
    {
        count = 0;
        return 0;
    }
        
    stringstream ss(lineStr);
	string str;
    point.header.seq = count;

    getline(ss, str, ',');
    point.x=atof(str.c_str());
    getline(ss, str, ',');
    point.y=atof(str.c_str());
    getline(ss, str, ',');
    point.z=atof(str.c_str());
    getline(ss, str, ',');
    point.theta=atof(str.c_str());
    getline(ss, str, ',');
    point.kappa=atof(str.c_str());
    getline(ss, str, ',');
    point.s=atof(str.c_str());
    getline(ss, str, ',');
    point.speed=atof(str.c_str());
    getline(ss, str, ',');
    point.accel=atof(str.c_str());
    getline(ss, str, ',');
    point.relative_time=atof(str.c_str());
    count++;
    return 1;
}

bool reader::saveOnce(car_msgs::trajectory_point point, int period){
    if(mode!=2){
        cout<<"mode err!";
        return 0;
    }
    static int count=0;
    count++;
    if(count>=period){
        count=0;
        cout<<"x:"<<point.x<<"  y:"<<point.y<<endl;
        outFile<<point.x<<",";
        outFile<<point.y<<",";
        outFile<<point.z<<",";
        outFile<<point.theta<<",";
        outFile<<point.kappa<<",";
        outFile<<point.s<<",";
        outFile<<point.speed<<",";
        outFile<<point.accel<<",";
        outFile<<point.relative_time<<",";
        outFile<<std::endl;
    }
    
    return 1;
}*/