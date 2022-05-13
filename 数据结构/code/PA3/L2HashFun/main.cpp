#include <cstdio>
#include <iostream>
#include "hashtable.h"
#include "time.h"
#include "fstream"

#define TABLE_SIZE 499883

// 1. naive hashing + linear probe
// 2. naive hashing + quadratic hueristic 
// 3. naive hashing + common overflow strategy
// 4. ascii hashing + linear probe
// 5. ascii hashing + quadratic heuristic
// 6. ascii hashing + common overflow strategy
// 7. utf-8 hashing + linear probe
// 8. utf-8 hashing + quadratic heuristic
// 9. utf-8 hashing + common overflow strategy
std::string hashingStrategies[3] = {"naive", "ascii", "utf-8"};
std::string collisionStrategies[3] = {"linear", "quadratic", "overflow"};

int main(int argc, char *argv[]){
#ifdef ORIGINAL
    int type;
    char buffer[1000];
    int data;
    // size of table, hashing_strategy, collision_strategy
    // hashtable table(43,new naive_hashing(),new linear_probe());
    hashtable table(TABLE_SIZE, new ascii_hashing(),new quadratic_probe());
#endif

#ifdef TESTING
    hashing_strategy* my_hashing;
    collision_strategy* my_collision;

    int hashingStrategyType;
    int collisionStrategyType;
    hashingStrategyType = std::atoi(argv[1]);
    collisionStrategyType = std::atoi(argv[2]);

    // select hashing strategy type
    if (hashingStrategyType == 0) my_hashing = new naive_hashing();
    else if (hashingStrategyType == 1) my_hashing = new ascii_hashing();
    else if (hashingStrategyType == 2) my_hashing = new utf8_hashing();

    // select collision strategy type
    if (collisionStrategyType == 0) my_collision = new linear_probe();
    else if (collisionStrategyType == 1) my_collision = new quadratic_probe();
    else if (collisionStrategyType == 2) my_collision = new overflow_probe();

    hashtable table(TABLE_SIZE, my_hashing, my_collision);

    // open file 
    std::string dataSetFolderPath = "testsets/";
    std::string dataSetFileString = dataSetFolderPath + argv[3] + ".in";
    const char* dataSetFileName = dataSetFileString.c_str();

    std::ifstream dataFile;
    dataFile.open(dataSetFileName);

    if (!dataFile) {
        printf("Unable to open dataFile %s\n", dataSetFileName);
        exit(1);   // call system to stop
    }

    char buffer[1000];
    int data;
    int type;
    clock_t startTime;
	startTime = clock();
    while (true) {
        dataFile >> type;
        if (type == 0) {
            dataFile >> buffer >> data;
            table.insert(hash_entry(buffer, data));
        } else if (type == 1) {
            dataFile >> buffer;
            table.query(buffer);
        } else break;
        clock_t operationTimeout = clock();
        if(((float) (operationTimeout - startTime)) / CLOCKS_PER_SEC >= 30) break;
    }
    clock_t endTime;
    endTime = clock();

    dataFile.close();

    // print out results to txt file
    std::string resultFilePath = "results/";
    // std::string resultFileString = resultFilePath + argv[3] + ".txt";
    std::string resultFileString = resultFilePath + "results.txt";
    const char* resultFileName = resultFileString.c_str();
    std::ofstream resultFile;
    resultFile.open(resultFileName, std::ios::app);

    if (!resultFile) {
        printf("Unable to open dataFile %s\n", resultFileName);
        exit(1);   // call system to stop
    }

    resultFile << dataSetFileName << "," <<
        hashingStrategies[hashingStrategyType] << "," <<
        collisionStrategies[collisionStrategyType] << "," <<
        "time: " << ((float)(endTime - startTime)) / CLOCKS_PER_SEC << "s," <<
        "i_collisions: " << table.insert_collision_count << "," << 
        "q_collisions: " << table.query_collision_count;
    resultFile << "\n";
    resultFile.close();

#endif





    



#ifdef ORIGINAL
    while(true){
        scanf("%d", &type);
        if(type == 0){
            scanf("%s", buffer);scanf("%d",&data);
            table.insert(hash_entry(buffer, data));
        }else if(type == 1){
            scanf("%s",buffer);
            printf("%d\n", table.query(buffer));
        }else break;
    }
    return 0;
#endif 
}