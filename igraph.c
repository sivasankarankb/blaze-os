// Inspiration Graphics Library

  int i,j,x,y,z,ab,xa,ya,xb,yb,m,n,color;
  unsigned char *gvidmem = (unsigned char *)0xA0000;
  
int plotpixel(int x, int y, int color){
  unsigned char *gvidmem = (unsigned char *)0xA0000;
  y*=320;
  gvidmem+=x+y;
  *gvidmem=color;           
  gvidmem-=x+y;
  return 0;  
}

int horline(xa,ya,xb,color){
for (i=xa; i<=xb; i++){
plotpixel(i,ya,color);
}
return 0;
}

int verline(xa,ya,yb,color){
for (i=ya; i<=yb; i++){
plotpixel(xa,i,color);
}
return 0;
}

int rect(xa,ya,xb,yb,color){
horline(xa,ya,xb,color);
verline(xb,ya,yb,color);
horline(xa,yb,xb,color);
verline(xa,ya,yb,color);
return 0;
}

int line(int x,int y,int xa,int ya,int color){
int deltax,deltay,ax,ay,d,ax2,ay2;
	  deltax = xa - x;
	  deltay = ya - y;
ax = x;
ay = y;
d = (2 * deltay) - deltax;
while(ax<=(xa/2)){
plotpixel(ax, ay, color);
plotpixel(ax2, ay2, color);
if(d < 0){
	d = d + (2 * deltay);
  }
else{
	d = d + 2 * (deltay - deltax);
	ay = ay + 1;
	ay2 = ay2 - 1;
  }
ax = ax + 1;
ax2 = ax2 - 1;
}
return 0;
}

int circle(int cx, int cy, int radius,int color){
int x,y,d;
d = 3 - (2 * radius);
x = 0;
y = radius;
while(x<=y){
plotpixel(cx + x, cy - y, color); //#1
plotpixel(cx + y, cy - x, color); //#2
plotpixel(cx + y, cy + x, color); //#3
plotpixel(cx + x, cy + y, color); //#4
plotpixel(cx - x, cy + y, color); //#5
plotpixel(cx - y, cy + x, color); //#6
plotpixel(cx - y, cy - x, color); //#7
plotpixel(cx - x, cy - y, color); //#8
if(d < 0){
	d = d + (4 * x) + 6;
  }
else{
	d = d + (4 * (x - y)) + 10;
	y = y - 1;
  }
x = x + 1;
}
return 0;
}