#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <set>
#include <cmath>
#include <stdio.h>
using namespace std;

class Film{
private:
    string name;
    double years;
    double rating;

public:
    Film (string n, double y, double r){
        name = n;
        years = y;
        rating = r;
    }

    double getRating() const {
        return rating;
    }

    double getYears() const{
        return years;
    }

    string getName() const{
        return name;
    }

    void print(ofstream &fout) const {
        fout << name << " - " << years << " - " << rating << endl; 
    }

    //------------------------------------------------------
    bool isGood() const{
        return rating >= 8;
    }
    //------------------------------------------------------
    bool isNew() const{
        return years  >= 2010;
    }
    //------------------------------------------------------
    double isAge () const{
        return (2025 - years);
    }
    //------------------------------------------------------
    bool newerThan(const Film &other) const{
        return years > other.getYears();
    }
    //------------------------------------------------------
    double isScore(const Film &other) const{
        double scorest = rating / (1 + (2025 - years));
        if(scorest < other.getRating() / (1 + (2025 - other.getYears()))){
            scorest = other.getRating() / (1 + (2025 - other.getYears()));
        }
        return scorest;
    }
    //------------------------------------------------------
    bool isOld(const Film &other) const{
        return years < other.getYears();
    }
    //------------------------------------------------------
    double isStable(double avg) const{
        return fabs(avg - rating);
    }
    

}; 

int main() {
    ifstream file("example.txt");
    if(!file.is_open()){
        cout << "Ошибка: не удалось открыть файл example.txt" << endl;
        return 1;
    }
    
    ofstream fout("for_example.txt");
    if(!fout.is_open()){
        cout << "Ошибка: не удалось открыть файл for_example.txt для записи" << endl;
        file.close();
        return 1;
    }
    
    vector<Film> films;
    
    string n;
    double y;
    double r; 

    while(file >> n >> y >> r){
        films.emplace_back(n, y, r);
    }

    file.close();
    //------------------------------------------------------
    fout << "Отсортированные фильмы по рейтингу:\n";
    sort(films.begin(), films.end(),
        [](const Film &a, const Film &b){
            return a.getRating() > b.getRating();
    });
    for(const Film &i : films){
        i.print(fout);
    }
    //------------------------------------------------------
    fout << "\nЛучшие фильмы:\n";
    for(const Film &i : films){
        if (i.isGood()) {
            i.print(fout);
        }
    }
    //------------------------------------------------------
    fout << "\nНовые фильмы:\n";
    for( auto i : films){
        if(i.isNew()){
            i.print(fout);
        }
    }
    //------------------------------------------------------
    fout << "\nВозраст фильмов:\n";
    for( auto i : films){
            fout << i.getName() << " - " << i.getYears() << " - " << i.getRating() << " - " << i.isAge() << endl; 
    }
    //------------------------------------------------------
    fout << "\nСамый новый фильм:\n";
    Film newer = films[0];
    for( auto i : films){
        if(i.newerThan(newer)){
            newer = i;
        }
    }
    newer.print(fout);
    //------------------------------------------------------
    fout << "\nФильм с наилучшим score:\n";
    Film best = films[0];
    for( auto i : films){
        if(i.isScore(best)){
            best = i;
        }
    } 
    best.print(fout);
    //------------------------------------------------------
    fout << "\nСамый старый фильм с рейтингом больше 8:\n";
    Film older_good = films[0];
    for( auto i : films){
        if(i.isGood()){
            if(i.isOld(older_good)){
                older_good = i;
            }
        }
    }
    older_good.print(fout);
    //------------------------------------------------------
    fout << "\nСамый стабильный фильм(который ближе всего к среднему рейтингу всех фильмов):\n";
    double avg = 0, sum = 0;
    for( auto i : films){
            sum += i.getRating();
        }
    avg = sum / films.size();
    Film stable = films[0];
    double stable_chet = stable.isStable(avg);

    for( auto i : films){
        if(i.isStable(avg) < stable_chet ){
            stable_chet = i.isStable(avg);
            stable = i;
        }
    }

    stable.print(fout);
    




    fout.close();
    return 0;
}