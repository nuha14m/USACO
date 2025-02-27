/**
 * Description: Pairs reduce frequency of collision
 * Source: own
 * Verification: Dec 17 Plat 1, CF Check Transcription
 * Dependency: Modular Int
 */

using namespace pairOp;

const int tmp = chrono::high_resolution_clock::now().time_since_epoch().count()%(MOD-1);

struct hsh {
    string S; 
    vpmi pows, ipows, cum;
    pmi base = mp(948392576,tmp+1), invbase; // probably want to randomize base
    
    hsh() {}
    hsh(string s) { init(s); }
    
    void init(string _S) {
        invbase = {1/base.f,1/base.s};
        S = _S; pows.resz(sz(S)), ipows.resz(sz(S)), cum.resz(sz(S)+1);
        pows[0] = ipows[0] = {1,1};
        FOR(i,1,sz(S)) pows[i] = pows[i-1]*base, ipows[i] = ipows[i-1]*invbase;
        F0R(i,sz(S)) cum[i+1] = cum[i]+pows[i]*(S[i]-'a'+1);
    }
    
    pmi get(int l, int r) {  return ipows[l]*(cum[r+1]-cum[l]); }
    
    int lcp(hsh& b) {
        int lo = 0, hi = min(sz(S),sz(b.S));
        while (lo < hi) {
            int mid = (lo+hi+1)/2;
            if (cum[mid] == b.cum[mid]) lo = mid;
            else hi = mid-1;
        }
        return lo;
    }
};

// hsh H("ababab"); F0R(i,6) FOR(j,i,6) ps(i,j,H.get(i,j));
