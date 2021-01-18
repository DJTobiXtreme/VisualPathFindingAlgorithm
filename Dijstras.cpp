#include "Dijstras.h"
#include <tuple>
#include <iostream>
using namespace std;

Dijstras::Dijstras ( ) : high(15), width(50),min(0),INF(15000), WALL(16000),
is_finished_iterate(false), is_finished_backtrace(false), is_started(false){
	
}

void Dijstras::Start (int sr, int sc, int fr, int fc) {
	this->sr = sr;
	this->sc = sc;
	this->fr = fr;
	this->fc = fc;
	for(int i=0;i<high;i++) { 
		for(int j=0;j<width;j++) {
			if (m[i][j]!=WALL){
				m[i][j] = INF;
				check[i][j] = 0;
			}
		}
	}
	m[sr][sc] = 0;
}

bool Dijstras::Iterate ( ) {

	

	
	tie(arow,acol) = findMinorUnchecked();
	
	if (arow==fr && acol==fc) {
		is_finished_iterate = true;
		return false;
	}

	if(arow == -1){
		is_finished_iterate = true;
		is_finished_backtrace = true;
		return false;
	}
	// arriba
	if (arow+1<high && m[arow+1][acol]==INF){
		m[arow+1][acol] = m[arow][acol]+1;
	}
	// derecha
	if (acol+1<width && m[arow][acol+1]==INF){
		m[arow][acol+1] = m[arow][acol]+1;
	}
	// abajo
	if (arow>0 && m[arow-1][acol]==INF){
		m[arow-1][acol] = m[arow][acol]+1;
		
	}
	// izquierda
	if (acol>0 && m[arow][acol-1]==INF){
		m[arow][acol-1] = m[arow][acol]+1;
	}
	

	return true;
}

tuple<int,int> Dijstras::findMinorUnchecked(){
	while(true){
		for(int i=0;i<high;i++) { 
			for(int j=0;j<width;j++) { 
				if(m[i][j]==min && check[i][j]==0){
					check[i][j] = 1;
					return make_tuple(i,j);
				}
			}
		}
		min++;
		if (min==INF) return make_tuple(-1,-1);
	}
}

void Dijstras::Draw ( ) {
	for(int i=0;i<width;i++) { 
		cout<<"/";
	}
	cout<<endl;
	for(int i=0;i<high;i++) { 
		for(int j=0;j<width;j++) { 
			cout<<m[i][j]<<" ";
		}
		cout<<endl;
	}
}

void Dijstras::Loop ( ) {
	if (is_finished_backtrace) return;
	else if (is_finished_iterate) Backtrace();
	else if (is_started) Iterate();
}

int Dijstras::getChecked (int i, int j) {
	return check[i][j];
}

bool Dijstras::Backtrace ( ) {
	min--;

	if (arow+1<high && m[arow+1][acol]==min){
		arow++; 
		check[arow][acol] = 9;
		return false;
	}
	// derecha
	if (acol+1<width && m[arow][acol+1]==min){
		acol++; 
		check[arow][acol] = 9;
		return false;
	}
	// abajo
	if (arow>0 && m[arow-1][acol]==min){
		arow--; 
		check[arow][acol] = 9;
		return false;
		
	}
	// izquierda
	if (acol>0 && m[arow][acol-1]==min){
		acol--; 
		check[arow][acol] = 9;
		return false;
	}

	is_finished_backtrace = true;
}



void Dijstras::SetWall (int x, int y) {
	if(y<high && x<width){
		m[y][x] = WALL;
		check[y][x] = 8;
	}
}

