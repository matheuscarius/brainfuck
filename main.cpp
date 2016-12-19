#include <cstdio>
#include <vector>

using namespace std;

vector<unsigned char> mem(1,0), code;
int mem_p, code_p, brkt;

void ptr_inc() {
  mem_p++;
  if(mem_p == mem.size())
    mem.push_back(0);
}
void ptr_dec() {
  mem_p--;
}
void val_inc() {
  mem[mem_p]++;
}
void val_dec() {
  mem[mem_p]--;
}
void output() {
  putchar(mem[mem_p]);
}
void input() {
  mem[mem_p]=getchar();
}
void open_brkt() {
  brkt++;
  if(!mem[mem_p]) {
    int match = brkt-1;
    while(brkt!=match) {
      code_p++;
      if(code[code_p]=='[') brkt++;
      else if(code[code_p]==']') brkt--;
    }
  }
}
void close_brkt() {
  brkt--;
  if(mem[mem_p]) {
    int match = brkt+1;
    while(brkt!=match) {
      code_p--;
      if(code[code_p]=='[') brkt++;
      else if(code[code_p]==']') brkt--;
    }
  }
}


int main (int argc, char **argv) {
  FILE *in;

  if(argc == 1) {
    printf("Usage:\n");
    printf("%s <file-name>\n", argv[0]);
    return -1;
  }
  else {
    in = fopen(argv[1], "r");
    if (in == NULL) {
      fprintf(stderr, "Error: could not open %s\n", argv[1]);
      return -1;
    }
  }

  while(!feof(in)) {
    code.push_back(fgetc(in));
  }

  for(code_p = 0; code_p < code.size(); code_p++) {
    char c;
    c = code[code_p];
    switch(c) {
      case '>':
        ptr_inc();
        break;
      case '<':
        ptr_dec();
        break;
      case '+':
        val_inc();
        break;
      case '-':
        val_dec();
        break;
      case '.':
        output();
        break;
      case ',':
        input();
        break;
      case '[':
        open_brkt();
        break;
      case ']':
        close_brkt();
        break;
      default:
        break;
    }
  }

}
