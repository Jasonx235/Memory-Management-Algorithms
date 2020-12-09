#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
vector<class Job> setJob();
vector<class Partition> setPartition();
void print(vector<class Job> jobList, vector<class Partition> partitionList, int totalWaste);
void FirstFit(vector<class Job>, vector<class Partition>);
void NextFit(vector<class Job>, vector<class Partition>);
void BestFit(vector<class Job>, vector<class Partition>);
void WorstFitFixed(vector<class Job>, vector<class Partition>);
void WorstFitDynamic(vector<class Job>, vector<class Partition>);


class Job {
public:
    Job() { name = -1, jobSize = 0, status = false, partitionNum = -1; }

    Job(int n, int size) {
        name = n;
        jobSize = size;
 
    }

    void setName(int n) {
        name = n;
    }

    void setSize(int size) {
        jobSize = size;
    }

    void setStatus(bool s) {
        status = s;
    }

    void setPartitionNum(double p) {
        partitionNum = p;
    }

    void setWaste(int w) {
        waste = w;
    }


    int getName() {
        return name;
    }

    int getSize() {
        return jobSize;
    }

    bool getStatus() {
        return status;
    }

    double getPartNum() {
        return partitionNum;
    }

    int getWaste() {
        return waste;
    }

private:
    int name, jobSize;
    bool status = false;
    double partitionNum = -1;
    int waste = -1;
};

class Partition {
public:
    Partition() { name = -1, size = 0, assigned = false, jobID = -1, waste = -1; }

    Partition(double n, int s) {
        name = n;
        size = s;
        assigned = false;
        waste = -1;
        jobID = -1;
    }

    void setName(double n) {
        name = n;
    }

    void setSize(int s) {
        size = s;
    }

    void setAssign(bool a) {
        assigned = a;
    }

    void setJobID(int j) {
        jobID = j;
    }

    void setWaste(int w) {
        waste = w;
    }
 

    double getName() {
        return name;
    }
    
    int getSize() {
        return size;
    }

    int getAssigned() {
        return assigned;
    }

    int getJobID() {
        return jobID;
    }

    int getWaste() {
        return waste;
    }

private:
    double name =-1;
    int size =-1;
    bool assigned = false;
    int jobID = -1;
    int waste =-1;
};


int main()
{
    vector<Job> jobList;
    vector<Partition> partitionList;

    jobList = setJob();
    partitionList = setPartition();

    FirstFit(jobList, partitionList);
    NextFit(jobList, partitionList);
    BestFit(jobList, partitionList);
    WorstFitFixed(jobList, partitionList);
    WorstFitDynamic(jobList, partitionList);

    return 0;
}

void print(vector<Job> jobList, vector<Partition> partitionList, int totalWaste)
{
    cout << "JOB ID" << setw(20) << "Partition ID" << setw(15) << "Waste" << setw(15) << "Status" << endl;
    string yesNo;

    for (int i = 0; i < jobList.size(); i++)
    {
        if (jobList[i].getStatus()) {
            yesNo = "running";
        }
        else
            yesNo = "waiting";
        cout << jobList[i].getName() << setw(20) << jobList[i].getPartNum() << setw(20) << jobList[i].getWaste() << setw(15) << yesNo << endl;
    }
    cout << "Total Waste: " << totalWaste << endl << endl;
}

vector<Job> setJob()
{
    vector<Job> jobList;
    int numofJobs, sizeOfJob;

    //Setting Up Jobs
    cout << "Enter the number of jobs: ";
    cin >> numofJobs;

    for (int i = 1; i <= numofJobs; i++)
    {
        cout << "Enter size for process " << i << ": ";
        cin >> sizeOfJob;
        jobList.push_back(Job(i, sizeOfJob));
    }
    cout << endl;
    return jobList;
}

vector<Partition> setPartition()
{
    vector<Partition> partitionList;
    int numOfPart, sizeOfPart;

    //Setting Up Partitions
    cout << "Enter the number of Partitions: ";
    cin >> numOfPart;

    for (int i = 1; i <= numOfPart; i++)
    {
        cout << "Enter size for partition " << i << ": ";
        cin >> sizeOfPart;
        partitionList.push_back(Partition(i, sizeOfPart));
    }

    return partitionList;

}

void FirstFit(vector<Job> jobList, vector<Partition> partitionList) {
    
    int totalWaste =0;
    for (int i = 0; i < jobList.size(); i++) {

        for (int j = 0; j < partitionList.size(); j++)
        {
            if ((jobList[i].getSize() <= partitionList[j].getSize()) && (!jobList[i].getStatus() && !partitionList[j].getAssigned()))
            {
                jobList[i].setStatus(true);
                jobList[i].setPartitionNum(partitionList[j].getName());
                partitionList[j].setWaste(partitionList[j].getSize() - jobList[i].getSize());
                jobList[i].setWaste(partitionList[j].getWaste());
                partitionList[j].setAssign(true);
                partitionList[j].setJobID(jobList[i].getName());
                totalWaste += partitionList[j].getWaste();
                break;
            }
        }
        
    }
    cout << "\n\n" << setw(40) << "First Fit Algorithm" << endl;
    print(jobList, partitionList, totalWaste);
}

void NextFit(vector<Job> jobList, vector<Partition> partitionList) {

    int j = 0, k=0;
    int totalWaste = 0;
    for (int i = 0; i < jobList.size(); i++)
    {
        while (k < partitionList.size())
        {
            if ((jobList[i].getSize() <= partitionList[j].getSize()) && (!jobList[i].getStatus() && !partitionList[j].getAssigned()))
            {
                jobList[i].setStatus(true);
                jobList[i].setPartitionNum(partitionList[j].getName());
                partitionList[j].setWaste(partitionList[j].getSize() - jobList[i].getSize());
                jobList[i].setWaste(partitionList[j].getWaste());
                partitionList[j].setAssign(true);
                partitionList[j].setJobID(jobList[i].getName());
                totalWaste += partitionList[j].getWaste();
                break;
            }
            k++;
            j = ((j + 1) % partitionList.size());
        }
    }
    cout << "\n\n" << setw(40) << "Next Fit Algorithm" << endl;
    print(jobList, partitionList, totalWaste);
}

void BestFit(vector<Job> jobList, vector<Partition> partitionList) {

    int totalWaste = 0;
    int BestID = -1;
  
    for (int i = 0; i < jobList.size(); i++)
    {
        BestID = -1;
       for(int j =0; j <partitionList.size(); j++)
        {
            if ((jobList[i].getSize() <= partitionList[j].getSize()) && (!jobList[i].getStatus() && !partitionList[j].getAssigned()))
            {
                if (BestID == -1) {
                    BestID = j;
                }
                else if (partitionList[BestID].getSize() > partitionList[j].getSize()) {
                    BestID = j;
                }
            }
        }

        if (BestID != -1)
        {
            jobList[i].setStatus(true);
            jobList[i].setPartitionNum(partitionList[BestID].getName());
            partitionList[BestID].setWaste(partitionList[BestID].getSize() - jobList[i].getSize());
            jobList[i].setWaste(partitionList[BestID].getWaste());
            partitionList[BestID].setAssign(true);
            partitionList[BestID].setJobID(jobList[i].getName());
            totalWaste += partitionList[BestID].getWaste();
        }
    }


    cout << "\n\n" << setw(40) << "Best Fit Algorithm" << endl;
    print(jobList, partitionList, totalWaste);

}

void WorstFitFixed(vector<Job> jobList, vector<Partition> partitionList) {

    int totalWaste = 0;
    int worstID = -1;

    for (int i = 0; i < jobList.size(); i++)
    {
        worstID = -1;
        for (int j = 0; j < partitionList.size(); j++)
        {
            if ((jobList[i].getSize() <= partitionList[j].getSize()) && (!jobList[i].getStatus() && !partitionList[j].getAssigned()))
            {
                if (worstID == -1) {
                    worstID = j;
                }
                else if (partitionList[worstID].getSize() < partitionList[j].getSize()) {
                    worstID = j;
                }
            }
        }

        if (worstID != -1)
        {

            jobList[i].setStatus(true);
            jobList[i].setPartitionNum(partitionList[worstID].getName());
            partitionList[worstID].setWaste(partitionList[worstID].getSize() - jobList[i].getSize());
            jobList[i].setWaste(partitionList[worstID].getWaste());
            partitionList[worstID].setAssign(true);
            partitionList[worstID].setJobID(jobList[i].getName());
            totalWaste += partitionList[worstID].getWaste();
        }
    }


    cout << "\n\n" << setw(40) << "Worst Fit (Fixed) Algorithm" << endl;
    print(jobList, partitionList, totalWaste);

}

void WorstFitDynamic(vector<Job> jobList, vector<Partition> partitionList) {

    int totalWaste = 0;
    int worstID = -1;

    for (int i = 0; i < jobList.size(); i++)
    {
        worstID = -1;
        for (int j = 0; j < partitionList.size(); j++)
        {
            if ((jobList[i].getSize() <= partitionList[j].getSize()) && (!jobList[i].getStatus() && !partitionList[j].getAssigned()))
            {
                if (worstID== -1) {
                    worstID = j;
                }
                else if (partitionList[worstID].getSize() < partitionList[j].getSize()) {
                    worstID = j;
                }
            }
        }

        if (worstID != -1)
        {
            
            jobList[i].setStatus(true);
            jobList[i].setPartitionNum(partitionList[worstID].getName());
            partitionList[worstID].setWaste(partitionList[worstID].getSize() - jobList[i].getSize());
            jobList[i].setWaste(partitionList[worstID].getWaste());
            partitionList[worstID].setAssign(true);
            partitionList[worstID].setJobID(jobList[i].getName());
  
            if (partitionList[worstID].getWaste() > 0)
            {
                partitionList.insert(partitionList.begin() + worstID + 1, Partition(partitionList[worstID].getName() + 0.1, partitionList[worstID].getWaste()));
                partitionList[worstID].setSize(partitionList[worstID].getSize() - partitionList[worstID].getWaste());
                partitionList[worstID].setWaste(0);
            }
            totalWaste += partitionList[worstID].getWaste();
        }
    }


    cout << "\n\n" << setw(40) << "Worst Fit (DYNAMIC) Algorithm" << endl;
    print(jobList, partitionList, totalWaste);


    cout << left << setw(20) << "Partitions" << setw(20) << "Partition Size" << setw(20) << "Job Assigned" << endl;
    for (int i = 0; i < partitionList.size(); i++)
    {
        cout << left << setw(25) << partitionList[i].getName() << setw(20) << partitionList[i].getSize() << setw(25) << partitionList[i].getJobID() << endl;
    }
}