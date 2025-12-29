/**
 * Author: Anonymous
 * Description: LazySegTree
 */

// Set BLOCK_SIZE to N^(2/3) for Mo's with updates
int BLOCK_SIZE = CHANGE; 

struct Query {
    int l, r, t, id;
    bool operator<(const Query& o) const {
        int l_block = l / BLOCK_SIZE;
        int o_l_block = o.l / BLOCK_SIZE;
        if (l_block != o_l_block) return l_block < o_l_block;
        int r_block = r / BLOCK_SIZE;
        int o_r_block = o.r / BLOCK_SIZE;
        if (r_block != o_r_block) return r_block < o_r_block;
        return t < o.t;
    }
};

struct Update {
    int pos, prev_val, new_val;
};

void solve_mo_with_updates() {
    // BLOCK_SIZE = pow(n, 2.0/3.0);

    vector<Query> queries;
    vector<Update> updates;
    // for (int i = 0; i < q; i++) {
    //     int type; cin >> type;
    //     if (type == 1) { // Query
    //         int l, r; cin >> l >> r; l--, r--;
    //         queries.push_back({l, r, (int)updates.size(), (int)queries.size()});
    //     } else { // Update
    //         int pos, val; cin >> pos >> val; pos--;
    //         updates.push_back({pos, 0, val}); // prev_val can be filled later
    //     }
    // }

    sort(all(queries));

    int ans = 0;
    auto add = [&](int idx) {};
    auto rem = [&](int idx) {};
    auto apply_update = [&](int update_idx, int current_l, int current_r) {
        auto& upd = updates[update_idx];
        // If update position is within current range [l, r], adjust answer
        if (upd.pos >= current_l && upd.pos <= current_r) {
            rem(upd.pos);
            a[upd.pos] = upd.new_val;
            add(upd.pos);
        } else {
            a[upd.pos] = upd.new_val;
        }
    };
    auto undo_update = [&](int update_idx, int current_l, int current_r) {
        auto& upd = updates[update_idx];
        if (upd.pos >= current_l && upd.pos <= current_r) {
            rem(upd.pos);
            a[upd.pos] = upd.prev_val;
            add(upd.pos);
        } else {
            a[upd.pos] = upd.prev_val;
        }
    };

    vector<int> out(queries.size());
    int cur_l = 0, cur_r = -1, cur_t = 0;
    for (auto& [l, r, t, id] : queries) {
        while (cur_t < t) apply_update(cur_t++, cur_l, cur_r);
        while (cur_t > t) undo_update(--cur_t, cur_l, cur_r);
        while (cur_l > l) add(--cur_l);
        while (cur_r < r) add(++cur_r);
        while (cur_l < l) rem(cur_l++);
        while (cur_r > r) rem(cur_r--);
        out[id] = ans;
    }
}
