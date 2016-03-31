#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

string buffer;
vector<long long> way_seq;
bool oneway;
bool oneway_reverse;
int way_level = 0;

void doit(string tag_name, unordered_map<string, string>& attr, bool open) {
  if (open) {
    if (tag_name == "way") {
      way_seq.clear();
      oneway = false;
      oneway_reverse = false;
      way_level = 0;
    } else if (tag_name == "nd") {
      way_seq.push_back(stoll(attr["ref"]));

    } else if (tag_name == "tag") {
      if (attr["k"] == "oneway") {
        if (attr["v"] == "true" || attr["v"] == "1") {
          oneway = true;
        } else if (attr["v"] == "-1" || attr["v"] == "referse") {
          oneway = true;
          oneway_reverse = true;
        }

      } else if (attr["k"] == "highway") {
        if (attr["v"] == "living_street" ||
            attr["v"] == "pedestrian" ||
            attr["v"] == "track" || 
            attr["v"] == "road" ||
            attr["v"] == "service") {
          way_level = 1;
        } else if (attr["v"] == "residential" ||
                   attr["v"] == "unclassified") {
          way_level = 2;
        } else if (attr["v"] == "tertiary" ||
                   attr["v"] == "tertiary_link") {
          way_level = 3;
        } else if (attr["v"] == "secondary" ||
                   attr["v"] == "secondary_link") {
          way_level = 4;
        } else if (attr["v"] == "primary" ||
                   attr["v"] == "primary_link") {
          way_level = 5;
        } else if (attr["v"] == "trunk" ||
                   attr["v"] == "trunk_link") {
          way_level = 6;
        } else if (attr["v"] == "motorway" ||
                   attr["v"] == "motorway_link") {
          way_level = 7;
        } else {
          way_level = 0;
        }
      }
    }
  } else {
    if (tag_name == "way") {
      if (oneway_reverse) reverse(way_seq.begin(), way_seq.end());
      if (way_level > 0) {
        for (size_t i = 1; i < way_seq.size(); ++i) {
          cout << way_level << "\t" << way_seq[i - 1] << "\t" << way_seq[i] << endl;
          if (!oneway) cout << way_level << "\t" << way_seq[i] << "\t" << way_seq[i - 1] << endl;
        }
      }
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
  if (tag_name != "way" &&
      tag_name != "nd" &&
      tag_name != "tag") return;
      

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

int main() {
  std::ios::sync_with_stdio(false);
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
  return 0;
}
