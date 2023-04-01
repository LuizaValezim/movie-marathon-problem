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
#include <map>
#include <ctime>

#ifndef BASIC_H
#define BASIC_H

using namespace std;

using map;
using bitset;
using vector;
using cin;
using cout;
using endl;

struct Movie{
    int start;
    int end;
    int genre;
};

void order_end(vector<Movie> &movies) {
    sort(movies.begin(), movies.end(), [] (Movie &a, Movie &b){
		return a.end < b.end;
	});
}

void order_start(vector<Movie> &movies) {

    for (int i = 0; i < int(movies.size()); i++){
        if (movies[i].end == movies[i+1].end){
            if (movies[i].start > movies[i+1].start) {
                Movie aux = movies[i];
                movies[i] = movies[i+1];
                movies[i+1] = aux;
            }
        }
    }
}

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

void greedy(vector<Movie> &movies, vector<int> &movie_by_genre, bitset<24> &free_time, vector<Movie> &vector_seen_movies, int &seen_movies) {

    for (int i = 0; i <int(movies.size()); i++){
        bitset<24> hour;
        fill_bitset(hour, movies[i].start-1, movies[i].end-1);
        if ((!(free_time & hour).any()) && (movie_by_genre[movies[i].genre-1] > 0)) {  
            vector_seen_movies.push_back(movies[i]);
            movie_by_genre[movies[i].genre-1]--;
            fill_bitset(free_time, movies[i].start-1, movies[i].end-1);
            return;
        }
    }
}


void randomness(vector<Movie> &movies, vector<int> &movie_by_genre, bitset<24> &free_time, vector<Movie> &vector_seen_movies, int &seen_movies) {
    vector<Movie> free_on_pause;
    if (int(movies.size()) > 1) {
        for (int i = 1; i < int(movies.size()); i++){
            bitset<24> hour;
            fill_bitset(hour, movies[i].start-1, movies[i].end-1);
            if ((!(free_time & hour).any()) && (movie_by_genre[movies[i].genre-1] > 0)) {    
                free_on_pause.push_back(movies[i]);
            }  
        }

        int random_int = 0;

        if (int(free_on_pause.size()) == 0){
            return;
        }
        if (free_on_pause.size() == 1){
            random_int = 0;
        } else{
            int size_myDictItem = int(free_on_pause.size()-1);
            srand(time(NULL));
            random_int = rand() % size_myDictItem+1;
        }

        seen_movies++;
        vector_seen_movies.push_back(free_on_pause[random_int]);
        movie_by_genre[free_on_pause[random_int].genre-1]--;
        fill_bitset(free_time, free_on_pause[random_int].start-1, free_on_pause[random_int].end-1);
    } 
}