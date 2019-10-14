#include "line.h"
using namespace std;

int main(int argc, char *argv[])  {
/*
  if (argc < 1 || (argc != 3 && argc != 2)) {
    cout << "Invalid arguments" << endl;
    return 1;
  }

  ArgumentManager am(argc, argv);
  const string in = am.get("input");
  const string out = am.get("output");
  ==================================== */
  string in = "input5.txt";
  string out = "output.txt";


  ifstream ifs(in);
  int tot = 0;
  string line;

  Thoughts dilemma;


  while(!ifs.eof()) {
    getline(ifs, line);
    if (line.length() == 0) continue; // wtf wrong with .eof() lol
    Line *tmp = new Line(line);
    dilemma.add_end(tmp);
    tot++;
  }
  if (tot == 0) { ofstream ofs(out); ofs.close(); }
  ifs.close();


  // dilemma.print();
  // dilemma.print_raw();
  cout << string(2, '\n');
  dilemma.connect();
  dilemma.reset();
  dilemma.connect();
  cout << "\n\nestablished connections:\n";
  dilemma.print();
  cout << "\n\nreordered:\n";
  dilemma.reorder();
  dilemma.print();
  dilemma.write(out);


  return 0;
}
