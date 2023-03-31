#include "basic.h"

using namespace std;

using map;
using bitset;
using vector;
using cin;
using cout;
using endl;

int main() {
    int n_movies, n_genres;
    cin >> n_movies>> n_genres;

    vector<int> movie_by_genre(n_genres, 0);
    Movie empty_movie = {0, 0, 0};
    vector<Movie> movies(n_movies, empty_movie);
    bitset<24> free_time;
    bitset<24> hour_mask(0xFFFFFF);
    vector<Movie> vector_seen_movies;
    int seen_movies= 0;

    for (int i = 0; i < n_genres; i++){
        cin >> movie_by_genre[i];
    }

    for (int i = 0; i < n_movies; i++){
        Movie movie;
        cin >> movie.start >> movie.end >> movie.genre;
        if (movie.start == 0){
            movie.start = 24;
        }
        if (movie.end == 0){
            movie.end = 24;
        }
        if (movie.start < 0){
            continue;
        }
        if (movie.end < 0){
            continue;
        }
        movies[i] = movie;
    }

    order_end(movies);
    order_start(movies);

    map<int, vector<Movie>> myDict;

    for (int i = 0; i < n_movies; i++){
        myDict[movies[i].end].push_back(movies[i]);
    }

    for (int i = 1; i <= 24; i++){
        if (free_time == hour_mask){
            break;
        }
        randomness(myDict[i], movie_by_genre, free_time, vector_seen_movies, seen_movies);
    }
   
    cout << "Foram vistos " << seen_movies<< " filmes." << endl;

    for (int i = 0; i < int(vector_seen_movies.size()); i++){
        cout << vector_seen_movies[i].start << " " << vector_seen_movies[i].end << " " << vector_seen_movies[i].genre << endl;
    }

    return seen_movies;
}