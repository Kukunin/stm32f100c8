int main()
{

  //Enable GPIO A clocking
  *(unsigned long*)(0x40021018) |= 0x4;

  //little delay for GPIOD get ready
  volatile unsigned long i=0;
  i++; i++; i++;
  i=0;

  //Set PA1 as General purpose output
  *(unsigned long*)(0x40010800) = 0x44444464;

  while(1)
  {
    //Turn LED ON
    *(unsigned long*)(0x40010810) = 0x2;
    //Delay
    for( i=0; i<1000000 ;++i );
    //Turn LED OFF
    *(unsigned long*)(0x40010814) = 0x2;
    //Delay
    for( i=0; i<1000000 ;++i );
  }

  return 0;
}
