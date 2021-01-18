#ifndef DIJSTRAS_H
#define DIJSTRAS_H
#include <tuple>
using namespace std;

class Dijstras {
public:
	Dijstras();
	void Start(int sr, int sc, int fr, int fc);
	void Loop();
	int getChecked(int i, int j);
	void SetWall(int i, int j);

	
	const int high;
	const int width;
	bool is_started;
private:
	bool Iterate();
	tuple<int,int> findMinorUnchecked();
	void Draw();
	bool Backtrace();
	
	int m[15][50];
	int check[15][50];
	int min;
	int arow;
	int acol;
	int sr;
	int sc;
	int fr;
	int fc;
	bool is_finished_iterate;
	bool is_finished_backtrace;
	const int INF;
	const int WALL;
};

#endif

