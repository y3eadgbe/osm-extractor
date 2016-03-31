#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*
 * Usage: ./toeps < file.graph > file.eps
 */


/*
 * Settings
 */
 
// edges of level less than min_way_level will be ignored (1-7)
const int min_way_level = 1;

// color of roads for each way level (RGB)
const double color[8][3] =
  {{0, 0, 0},
   {0.69, 0.89, 1},
   {0.58, 0.81, 0.95},
   {0.48, 0.74, 0.89},
   {0.38, 0.66, 0.85},
   {0.28, 0.59, 0.80},
   {0.18, 0.51, 0.75},
   {0.08, 0.44, 0.7}};

// linewidth for each way level
const double linewidth[8] = {1, 0.3, 0.5, 0.8, 1, 1, 1.3, 1.3};



const double inf = 1e10;

int main() {
  ios::sync_with_stdio(false);

  cout << "\%!PS-Adobe-2.0" << endl
       << "\%\%BoundingBox: -1025 -1025 1025 1025" << endl
       << "\%\%Orientation: Landscape" << endl
       << "\%\%Pages: 1" << endl
       << "\%\%EndComments" << endl
       << "/m {moveto} def" << endl
       << "/l {lineto} def" << endl
       << "/s {stroke} def" << endl
       << "1 setlinejoin" << endl;

  double bbtop = -inf, bbbot = inf, bbleft = inf, bbright = -inf;
  size_t N;
  cin >> N;
  vector<double> vx(N), vy(N);
  for (size_t i = 0; i < N; ++i) {
    double x, y;
    cin >> x >> y;
    constexpr double pi = acos(-1);
    x *= pi / 180.0;
    y *= pi / 180.0;
    y = atanh(sin(y));
    vx[i] = x;
    vy[i] = y;
    bbtop = max(bbtop, y);
    bbbot = min(bbbot, y);
    bbleft = min(bbleft, x);
    bbright = max(bbright, x);
  }

  double bbcx = (bbleft + bbright) / 2, bbcy = (bbtop + bbbot) / 2;
  double scale = max(bbright - bbleft, bbtop - bbbot) / 2;
  
  size_t M;
  cin >> M;
  vector<size_t> level(M), u(M), v(M);
  for (size_t i = 0; i < M; ++i) {
    cin >> level[i] >> u[i] >> v[i];
  }
  for (size_t l = min_way_level; l <= 7; ++l) {
    cout << linewidth[l] << " setlinewidth" << endl;
    cout << color[l][0] << " " << color[l][1] << " " << color[l][2] << " setrgbcolor" << endl;
    for (size_t i = 0; i < M; ++i) {
      if (level[i] != l) continue;
      cout << "newpath" << endl;
      cout << (vx[u[i]] - bbcx) / scale * 1000 << " " << (vy[u[i]] - bbcy) / scale * 1000 << " m" << endl; 
      cout << (vx[v[i]] - bbcx) / scale * 1000 << " " << (vy[v[i]] - bbcy) / scale * 1000 << " l" << endl;
      cout << "s" << endl;
    }
  }
  
  cout << "showpage" << endl;
  return 0;
}
