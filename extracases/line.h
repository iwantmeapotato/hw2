#include<iostream>
#include<fstream>
#include<sstream>
#include "ArgumentManager.h"
using namespace std;

const int MAX_LINES = 1000;

class Line {
public:
  Line *next;
  bool placed, cliff;
  string line, first, last, words[MAX_LINES];
  int num_words = 0;
  Line(string line = "") : next(0), placed(false), cliff(false), line(line), num_words(0) {
    stringstream rich(line);
    while (rich >> words[num_words]) {
      num_words++;
    }
    clean();
  }
  void clean() {
    for (int i = 0; i < num_words; i++) {
      string word = words[i];
      string clean_w;
      for (char letter : word) {
        if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) {  //alphabet
          if (letter >= 'A' && letter <= 'Z') letter += 32; //lowercase it
          clean_w += letter;
        }
      }
      words[i] = clean_w;
    }
    first = words[0];
    last = words[num_words - 1];
  }


};

class Thoughts {
public:
  Line *head, *tail;
  int lines;
  Thoughts() : head(0), tail(0), lines(0) {}

  bool empty() { if (head == 0) return true; return false; }

  void add_beg(Line *line) {
    if (empty()) { head = tail = line; tail->next = head; lines++; return; }
    line->next = head;
    head = line;
    tail->next = head;
    lines++;
  }

  void add_end(Line *line) {
    if (empty()) { add_beg(line); return; };
    tail->next = line;
    tail = line;
    tail->next = head;
    lines++;
  }

  void print() {
    Line *cu = head;
    for (int i = 0; i < lines; i++) {

      cout << cu->line;
      if (cu == head) cout << " < H";
      if (cu == tail) cout << " < T";
      cout << '\n';
      cu = cu->next;
    }
    cout << '\n';
  }

  void write(string file) {
    ofstream ofs(file);
    Line *cu = head;
    for (int i = 0; i < lines; i++) {

      ofs << cu->line;
      ofs << '\n';
      cu = cu->next;
    }
    // ofs << '\n';
    ofs.close();
  }


  void print_raw() {
    Line *cu = head;
    do {
      for (int i = 0; i < cu->num_words; i++) {
        cout << cu->words[i] << " ";
      }
      cout << '\n';
      cu = cu->next;
    }
    while (cu != head);
  }

  void fix_tail() {
    Line *cu = head;
    for (int i = 0; i < lines - 1; i++) {
      cu = cu->next;
    }
    tail = cu;
    cu->next = head;
  }


void connect() {
  if ((lines == 0) || (lines == 1)) return;

  Line *cu = head;
  Line *prev = tail;
  for (int i = 0; i < lines; i++) {
    Line *tester = head;
    Line *t_prev = tail;
    while (cu->placed) { cu = cu->next; }
    cu->placed = true;
    cout << "\nword: " << cu->last << '\n';
    for (int j = 0; j < lines; j++) {
      if (tester->first == cu->last) {

        if (tester == head) { head = cu; }
        t_prev->next = tester->next;
        if (i < j) tester->next = cu->next;
        else prev->next = cu->next;
        cu->next = tester;

        fix_tail();
        break;
      }
      if (j == lines - 1) cu->cliff = true;
      tester = tester->next;
      t_prev = t_prev->next;
    }
    print();

    cu = cu->next;
    prev = prev->next;
  }
}

void reset() {
  Line *reset = head;
  for (int i = 0; i < lines; i++) {
    reset->placed = false;
    reset = reset->next;
  }
}


/*
  void connect() {
    Line *m_prev = tail;
    Line *main = head;
    if ((lines == 0) || (lines == 1)) return;
    for (int i = 0; i < lines; i++) {
      while (main->placed) { main = main->next; }
      main->placed = true;
      string tail_w = main->words[main->num_words - 1];
      Line *t_prev = head;
      Line *tester = head->next;

      for (int j = 0; j < lines; j++) {
          cout << tester->words[0] << " = " << tail_w << '\n';


          if (tester->words[0] == tail_w) {
            cout << "\n\nCONNECT\ncu:\t"<<main->line<<"\nto\nmatch:\t"<<t_prev->next->line<<"\nt_prev:\t"<<t_prev->line<<"\n\n";

            Line *match = tester;

          //  OBJECTIVE: connect MATCH to END of MAIN
          //  AKA MATCH AFTER MAIN
          bool m_head = false;
          Line *tmp_sec = 0;
          if (match == head) {
            tmp_sec = head->next;
            head = main;
            m_head = true;
          }
          // if (match == tail) tail = main;
          // if (main == head) head = match;
          // if (main == tail) tail = match;

          t_prev->next = match->next;
          match->next = main->next;
          if (m_head) {
            match->next = tmp_sec;
            m_prev->next = main->next;
          }

          main->next = match;
          tail = match;

            fix_tail();
            print();
            break;
          // }
          }
          if (j == lines - 1) main->cliff = true;
          t_prev = t_prev->next;
          tester = tester->next;
      }

      main = main->next;
      m_prev = m_prev->next;
    }

  }

  */

  void reorder() {
    Line *main = head;
    if ((lines == 0) || (lines == 1)) return;
    for (int i = 0; i < lines; i++) {
      if (main->cliff) {
        head = main->next ;
        fix_tail();
        return;
      }
      main = main->next;
    }
  }


};
