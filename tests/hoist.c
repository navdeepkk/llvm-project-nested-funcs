struct s_foo10 {};

struct s_foe21 {
  struct s_foo10 *__s;
  int *x;
};

struct s_bar12 {
  struct s_foo10 *__s;
  int *x;
};

struct s_label13 {
  struct s_bar12 *__s;
};

void foo10(struct s_foo10 *);
void bar12(struct s_bar12 *);
void foe21(struct s_foe21 *);
void label13(struct s_label13 *);

#include <stdio.h>

void foo() { int x; }

int main() {
  foo();

  struct s_foo10 sfoo10;
foo10 : {
  int x;
  struct s_bar12 sbar12;
  sbar12.__s = __s;
  sbar12.x = &x;
bar12 : {
  struct s_label13 slabel13;
  slabel13.__s = __s;
label13 : { foo10(__s->__s->__s); }
}
  if (1) {
    bar12(&sbar12);
  }
  bar12(&sbar12);
  struct s_foe21 sfoe21;
  sfoe21.__s = __s;
  sfoe21.x = &x;
foe21 : {
  struct s_bar12 sbar1222;
  sbar1222.__s = __s->__s;
  sbar1222.x = __s->x;
  bar12(&sbar1222);
}
  foo10(__s);
  int a;
}

  foo10(&sfoo10);
}
