#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x , y , z;
};

double dist(Point A , Point B) {
    double dx = A.x-B.x;
    double dy = A.y-B.y;
    double dz = A.z-B.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

double brute(vector<Point>& pts , int l , int r) {
    auto ans=DBL_MAX;
    for (int i=l;i <= r ; i++) {
        for (int j=i+1 ; j <= r; j++) {
            ans=min(ans , dist(pts[i] , pts[j]));
        }
    }
    return ans;
}

double closestUtil(vector<Point>& pts , int l , int r) {
    if (r - l <= 3) {
        return brute(pts , l , r);
    }

    int mid= (l+r)/2;
    double midX=pts[mid].x;

    double d = min( closestUtil(pts , l , mid) , closestUtil(pts , mid+1 , r));

    vector<Point> slab;
    for (int i = l; i <= r; i++)
        if (abs(pts[i].x - midX) < d)
            slab.push_back(pts[i]);

    sort(slab.begin(), slab.end(), [](const Point &a, const Point &b) {
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    });

    for (int i = 0; i < slab.size(); i++) {
        for (int j = i + 1; j < slab.size(); j++) {
            if (slab[j].y - slab[i].y >= d) break;
            if (abs(slab[j].z - slab[i].z) < d)
                d = min(d, dist(slab[i], slab[j]));
        }
    }

    return d;
}

int main()
{
    int n;
    cin >> n;
    vector<Point> pts(n);
    for (int i=0;i<n;i++) {
        Point A;
        cin >> A.x >> A.y >> A.z;
        pts[i]= A;
    }
    sort(pts.begin() , pts.end() , [](const Point& a , const Point& b) {
        return a.x < b.x;
    });
    cout << fixed << setprecision(6) << closestUtil(pts, 0, n - 1) << "\n";
}
