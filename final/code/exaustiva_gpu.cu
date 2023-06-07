#include <thrust/host_vector.h>
#include <thrust/sequence.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/copy.h>

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> 
#include <random>
#include <chrono>
#include <stdlib.h> 
#include <iterator>
#include <random>
#include <chrono>
#include <fstream>
#include <bit>
#include <bitset>
#include <cstdint>
#include <stack>
#include <utility>
#include <map>
#include <ctime>
#include <omp.h>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::bitset;
using std::map;
using std::stack;
using std::pair;
using std::make_pair;

void time_schedule(int &free_time, int start, int end){
    for (int i = 0; i < 24; i++){
        if (i >= start && i < end){
            free_time  |= (1 << i);
        }
        else if (start > end && (i >= start || i < end)){
            free_time |= (1 << i);
        }
        else if(start == end){
            free_time |= (1 << i);
        }
    }
}

struct Movie{
    int start;
    int end;
    int genre;
};


struct exaustiva 
{  
    int n_movies;
    int n_genres;
    int* movies_by_genre;
    int* movies_time;
    int* movies_genre;


    exaustiva(int n_movies_, int n_genres_, int* movies_by_genre_, int* movies_time_, int* movies_genre_) : 
    n_movies(n_movies_), n_genres(n_genres_), movies_by_genre(movies_by_genre_), movies_time(movies_time_), movies_genre(movies_genre_) {}
    
    
    __host__ __device__
    int operator()(const int& config) {

        int free_time = 0;
        int n_movie = 0;
        int movies_by_genre_aux[20];
        
        for (int i = 0; i < n_genres; i++){
            movies_by_genre_aux[i] = *(movies_by_genre+i);
        }
        
        for (int i = 0; i < n_movies; i++){
            if (config & (1 << i)){
                if (movies_by_genre_aux[movies_genre[i]-1] > 0){
                    int a_time = free_time & *(movies_time + i);
                    if (((a_time) != 0)) return false;
                    movies_by_genre_aux[movies_genre[i]-1]--;
                    free_time = free_time | *(movies_time + i);
                    n_movie++;
                }
            }
        
        }

        return n_movie;
    }
};



int main(){
    int n_movies, n_genres;
    cin >> n_movies >> n_genres;

    thrust::host_vector<int> movies_by_genre(n_genres, 0);
    Movie empty_movie = {0, 0, 0};
    vector<Movie> movies (n_movies, empty_movie);

    for (int i = 0; i < n_genres; i++){
        cin >> movies_by_genre[i];
    }

    for (int i = 0; i < n_movies; i++){
        Movie movie;
        cin >> movie.start >> movie.end >> movie.genre;
        if (movie.start == 0) movie.start = 24;
        if (movie.end == 0) movie.end = 24;
        if (movie.start < 0 || movie.end < 0) continue;

        movies[i] = movie;
    }

    thrust::host_vector<int> movies_genre(n_movies);
    thrust::host_vector<int> movies_times(n_movies); 


    for (int i = 0; i < n_movies; i++){
        movies_times[i] = 0;
        time_schedule(movies_times[i], movies[i].start-1, movies[i].end-1);
        movies_genre[i] = movies[i].genre;
    }

    thrust::device_vector<int> config_vector(pow(2, n_movies));
    thrust::sequence(config_vector.begin(), config_vector.end());
    thrust::device_vector<int> movies_genre_gpu(movies_genre);
    thrust::device_vector<int> movies_times_gpu(movies_times);
    thrust::device_vector<int> movies_by_genre_gpu(movies_by_genre);
    thrust::transform(config_vector.begin(), config_vector.end(), config_vector.begin(), exaustiva(n_movies, n_genres, raw_pointer_cast(movies_by_genre_gpu.data()), raw_pointer_cast(movies_times_gpu.data()), raw_pointer_cast(movies_genre_gpu.data())));
    thrust::host_vector<int> config_vector_final = config_vector;
    
    int max_count = 0;
    int iters = pow(2, n_movies);
    for (int i = 0; i < iters; i++){
        if (config_vector_cpu_final[i] > max_count){
            max_count = config_vector_final[i];
        }
    }

    cout << max_count << " movies watched." << endl;
}
