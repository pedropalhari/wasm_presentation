
int square(int n)
{
  int x = 0;
  for (long i = 0; i < 1000000; i++)
    x = n * n;

  return 0;
}

int main()
{
  square(100);

  return 0;
}