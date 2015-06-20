# include <stdio.h>
# include <math.h>
double v[] = {0.0, 0.0, 2.0};
double r = 1.0;
double xmin = -1.0, xmax = 1.0;
double ymin = -1.0, ymax = 1.0;
int rx = 100, ry = 100;
double image[100][100];
double l[] = {0.57735, 0.57735, 0.57735};

void traceIt(void);
void write2file(void);

int main(void) {
    traceIt();
    write2file();
    return 1;
}

void traceIt(void) {
     double dx, dy;
     dx = (xmax - xmin)/rx;
     dy = (ymax - ymin)/ry;
     double delx, dely, delz;
     double a, b, c, disc;

     c = v[0]*v[0] + v[1]*v[1] + v[2]*v[2] - r*r;

     delz = -v[2];
     
     double t, t1, t2, dotprod, x, y;
     double xs, ys, zs;     
     int i, j;
     for(x = xmin, i = 0; x < xmax; x += dx, ++i) {
           delx = x;
           for(y = ymin, j = 0 ; y < ymax; y += dy, ++j) {
                 dely = y;
                 a = delx*delx + dely*dely + delz*delz;
                 b = 2.0 * (delx * v[0] + dely * v[1] + delz * v[2]);
                 disc = b * b - 4.0 * a * c;
                 printf("a: %lf b: %lf c: %lf disc: %lf\n", a, b, c, disc);
                 if(disc < 0.0) {
                         image[i][j] = 0.0;
                         continue;
                 }
                 else {
                      t1 = (-b + sqrt(disc))/(2*a);
                      t2 = (-b - sqrt(disc))/(2*a);
                      if(t1 <= t2) t = t1;
                      else t = t2;
                 }
                 xs = v[0] + t * delx;
                 ys = v[1] + t * dely;
                 zs = v[2] + t * delz;
                 dotprod = l[0]*xs + l[1]*ys + l[2] * zs;
                 if(dotprod < 0.0) image[i][j] = 0.0;
                 else  image[i][j] = dotprod;
           }
     }
}

void write2file(void) {
     FILE *img;
     img = fopen("image.out", "w");
     int i, j;
     for(i = 0; i < rx; ++i)
           for(j = 0; j < ry; ++j)
                 fprintf(img, "%lf\n", image[i][j]);
     fclose(img);
}
