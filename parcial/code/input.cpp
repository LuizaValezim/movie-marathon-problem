#include <chrono>
#include <random>
#include <fstream>
#include <boost/random.hpp>

using namespace std;

int main (int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);

    ofstream inputFile;
    inputFile.open("input.txt");
    inputFile << n << " " << m << endl;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);

    normal_distribution<double> distribution_dif(2, 1.0);
    uniform_int_distribution<int> distribution_hr(0, 21);
    uniform_int_distribution<int> distribution_cat(1, m);

    vector<int> maxMovies(m); 
    for (int i = 0; i < m; i++) {
        maxMovies[i] = distribution_cat(generator); 
        inputFile << maxMovies[i] << " "; 
    }
    inputFile << endl;

    for (int i = 0; i < n; i++) {
        int start = distribution_hr(generator);
        double difference = distribution_dif(generator);
        int end = ((int)start + (int)round(difference)) % 24;
        int genre = distribution_cat(generator);

        inputFile << start << " " << end << " " << genre << endl;
    }

    inputFile.close();
    return 0;
}