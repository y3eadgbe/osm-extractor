#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <google/sparse_hash_map>
#include <iomanip>

using namespace std;

string buffer;

long long N, M;
google::sparse_hash_map<long long, long long> dic;
vector<double> lon, lat;

void doit(string tag_name, unordered_map<string, string>& attr, bool open) {
  if (open) {
    long long id = stoll(attr["id"]);
    if (dic.find(id) != dic.end()) {
      long long v = dic[id];
      lon[v] = stod(attr["lon"]);
      lat[v] = stod(attr["lat"]);
    }
  }
}

void parse_tag(string str) {
  bool open = (str[0] != '/');
  if (!open) str = str.substr(1);
  stringstream ss(str);
  string tag_name;
  size_t itr = 0;
  for (; itr < str.size(); ++itr) {
    if (str[itr] == ' ' || str[itr] == '/') break;
  }
  tag_name = str.substr(0, itr);

  //pruning
  if (tag_name != "node") return;

  unordered_map<string, string> attr;

  {
    string attr_name;
    bool attr_mode = true;
    int start_it = itr;
    for (; itr < str.size(); ++itr) {
      if (attr_mode) {
        if (str[itr] == ' ') {
          start_it = itr + 1;
        } else if (str[itr] == '=') {
          attr_name = str.substr(start_it, itr - start_it);
          attr_mode = false;
          ++itr;
          start_it = itr + 1;
        }
      } else {
        if (str[itr] == '"') {
          attr_mode = true;
          attr[attr_name] = str.substr(start_it, itr - start_it);
        }
      }
    }
  }
  doit(tag_name, attr, open);
}

int main(int argc, char** argv) {
  std::ios::sync_with_stdio(false);

  if (argc < 2) return 0;
  ifstream fs(argv[1]);

  vector<long long> l, u, v;
  {
    long long itr = 0;
    long long a, b, c;
    while (fs >> a >> b >> c) {
      l.push_back(a);
      u.push_back(b);
      v.push_back(c);
      if (dic.find(b) == dic.end()) {
        dic[b] = itr++;
      }
      if (dic.find(c) == dic.end()) {
        dic[c] = itr++;
      }
    }
    N = itr;
    M = l.size();
    lon = vector<double>(N);
    lat = vector<double>(N);
  }
  
  {
    string line;
    size_t itr = 0;
    size_t open_itr = 0;
    size_t delete_itr = 0;
    bool close_mode = false;
    while (getline(cin, line)) {
      buffer += " " + line;
      while (itr < buffer.size()) {
        if (close_mode) {
          if (buffer[itr] == '>') {
            close_mode = false;
            parse_tag(buffer.substr(open_itr + 1, itr - open_itr - 1));
            delete_itr = itr + 1;
          }
        } else {
          if (buffer[itr] == '<') {
            close_mode = true;
            open_itr = itr;
            delete_itr = itr;
          }
        }
        itr++;
      }
      buffer = buffer.substr(delete_itr);
      itr -= delete_itr;
      open_itr -= delete_itr;
      delete_itr = 0;
    }
  }

  cout << N << endl;
  cout << setprecision(6) << fixed;
  for (long long i = 0; i < N; ++i) {
    cout << lon[i] << "\t" << lat[i] << endl;
  }
  cout << M << endl;
  for (long long i = 0; i < M; ++i) {
    cout << l[i] << "\t" << dic[u[i]] << "\t" << dic[v[i]] << endl;
  }
  return 0;
}
