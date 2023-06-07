#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm> 
#include <random>
#include <chrono>
#include <stdlib.h> 
#include <random>
#include <chrono>
#include <fstream>
#include <bitset>
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

void fill_bitset(bitset<24> &free_time, int start, int end) {
    for (int i = 0; i < 24; i++){
        if (i >= start && i < end){
            free_time.set(i);
        }
        else if (start > end && (i >= start || i < end)) {
            free_time.set(i);
        }
        else if(start == end){
            free_time.set(start);
        }
    }
}

struct Movie{
    int start;
    int end;
    int genre;
};

struct ProcessedMovie{
    int category;
    bitset<24> time;
};

struct Schedule{
    vector<int> movies;
    int total_movies;
};


void exaustiva(int n, vector<ProcessedMovie> &movies, vector<int> movie_by_genre, vector<bitset<64>> &schedule_total){

    long int combinations = pow(2, n);
    cout << combinations << endl;
    long int i;

    #pragma omp parallel 
    { 
        vector<bitset<64>> private_schedule_total;

        #pragma omp parallel for private(schedule_total) 

        for (i = 0; i < combinations; i++){

            bitset<24> free_time;
            bitset<64> movies_new(i);
            vector<int> movie_by_genre_new = movie_by_genre;

            for (int j = 0; j < n; j++){

                if (movies_new[j] == 1){

                    bitset<24> checked_time = free_time & movies[j].time;

                    if (checked_time != 0) {break;}

                    if (movie_by_genre_new[movies[j].genre-1] == 0) {break;}

                    movie_by_genre_new[movies[j].genre-1]--;

                    free_time |= movies[j].time;
                }
                if (j == n-1){
                    private_schedule_total.push_back(movies_new);
                }
            }
        }
        #pragma omp critical
        schedule_total.insert(schedule_total.end(), private_schedule_total.begin(), private_schedule_total.end());
    }
}


int main(){
    int n_movies, n_genre;
    cin >> n_movies >> n_genre;

    int max = 0;
    int i_best_schedule = 0;
    int n_schedules = schedules.size();

    vector<Schedule> vector_struct_schedules(n_schedules); 
    vector<int> movies_by_genre(n_genre, 0);
    vector<Movie> vector_movies (n_movies, empty_movie);
    vector<ProcessedMovie> pmovie_vector(n_movies, empty_pmovie);
    vector<bitset<64>> schedules;

    Movie empty_movie = {0, 0, 0};
    ProcessedMovie empty_pmovie = {0, 0x000000};

    for (int i = 0; i < n_genre; i++){
        cin >> movies_by_genre[i];
    }

    for (int i = 0; i < n_movies; i++){
        Movie movie;
        cin >> movie.start >> movie.end >> movie.genre;
        if (movie.start == 0) movie.start = 24;
        if (movie.end == 0) movie.end = 24;
        if (movie.start < 0 || movie.end < 0) continue;

        movies[i] = filme;
    }

    for (int i = 0; i < n_movies; i++){
        ProcessedMovie pmovie;
        pmovie.genre = movies[i].genre;
        fill_bitset(pmovie.horario, movies[i].start-1, movies[i].end-1);
        pmovie_vector[i] = pmovie;
    }

    exaustiva(n_movies, pmovie_vector, movies_by_genre, schedules);

    for (int i = 0; i < n_schedules; i++){
        Schedule schedule;
        schedule.n_movies = 0;
        for (int j = 0; j < 64; j++){
            if (schedules[i][j] == 1) {
                schedule.movies_new.push_back(j);
                schedule.n_movies++;
            } 
        }
        vector_struct_schedules[i] = schedule;
    }

    for (int i = 0; i < n_schedules; i++){
        if (vector_struct_schedules[i].n_movies > max){
            max = vector_struct_schedules[i].n_movies;
            i_best_schedule = i;
        }
    }

    Schedule bestMovies = vector_struct_schedules[i_best_schedule];
    vector<int> best_schedule = bestMovies.movies_new;

    cout << bestMovies.n_movies << " were watched." << endl;

    for (int i = 0; i < bestMovies.n_movies; i++){
        cout << movies[best_schedule[i]].start << " " << movies[best_schedule[i]].end << " " << movies[best_schedule[i]].genre << endl;
    }


    return bestMovies.n_movies;
}
