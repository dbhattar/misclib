#include <utility>
#include <string>
#include <vector>

using namespace std;

class HashMap
{
private:
  unsigned long hash(const string & key);
  void rehash();
public:
  HashMap();
  ~HashMap();

  void insert(const pair<string, string> entry);
  bool hasKey(const string & key) const;
  void deleteKey(const string & key);
  unsigned long size();
private:
  unsigned long m_size;
  vector<pair<string, string>> m_map;
  vector<bool> m_mapSet;
};
