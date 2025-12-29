/**
 * Author: Anonymous
 */
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_multiset;
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    ordered_set;
// find_by_order returns iterator to kth largest (0-indexed)
// order_of_key returns number of elements strictly less than given value -->
// basically index (0-indexed) for multiset, to erase use upper_bound.
// Upper_bound lower_bound exchange their roles
#define ONLINE_JUDGE
#ifndef ONLINE_JUDGE
#define db(x) cerr << #x << " == " << x << endl
#define dbs(x) cerr << x << endl
#else
#define db(x) ((void)0)
#define dbs(x) ((void)0)
#endif

#define int long long
#define fast() ios_base::sync_with_stdio(0); cin.tie(NULL);                                                               \
#define prDouble(x) cout << fixed << setprecision(10) << x
