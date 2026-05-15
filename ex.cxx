#include <vector>
#include <cmath>

using namespace std;

// ==========================================
// EJERCICIO 3
// ==========================================
double mean(vector<double> v) {
    if (v.empty()) return 0.0;
    double sum = 0.0;
    for (double x : v) sum += x;
    return sum / v.size();
}

double variance(vector<double> v) {
    if (v.size() < 2) return 0.0;
    double m = mean(v);
    double sum_sq = 0.0;
    for (double x : v) sum_sq += (x - m) * (x - m);
    return sum_sq / (v.size() - 1); 
}

// ==========================================
// EJERCICIO 4
// ==========================================
double pearson_r(vector<double> A, vector<double> B) {
    if (A.size() != B.size() || A.empty()) return 0.0;
    
    double mean_A = mean(A);
    double mean_B = mean(B);
    
    double num = 0.0, den_A = 0.0, den_B = 0.0;
    for (size_t i = 0; i < A.size(); i++) {
        double da = A[i] - mean_A;
        double db = B[i] - mean_B;
        num += da * db;
        den_A += da * da;
        den_B += db * db;
    }
    
    double den = sqrt(den_A * den_B);
    if (den == 0.0) return 0.0;
    return num / den;
}

// ==========================================
// EJERCICIO 5
// ==========================================

static long long decode_to_val(vector<char> s, int base) {
    long long val = 0;
    for (char c : s) {
        val *= base;
        if (c >= '0' && c <= '9') val += (c - '0');
        else if (c >= 'A' && c <= 'F') val += (c - 'A' + 10);
        else if (c >= 'a' && c <= 'f') val += (c - 'a' + 10); 
    }
    return val;
}

static vector<char> encode_from_val(long long n, int base) {
    if (n == 0) return {'0'};
    vector<char> res;
    while (n > 0) {
        int rem = n % base;
        res.push_back(rem < 10 ? '0' + rem : 'A' + (rem - 10));
        n /= base;
    }
    
    int len = res.size();
    for(int i = 0; i < len / 2; i++) {
        char temp = res[i];
        res[i] = res[len - 1 - i];
        res[len - 1 - i] = temp;
    }
    return res;
}


vector<char> dec_to_septapus(int n) { return encode_from_val(n, 7); }
vector<char> dec_to_octopus(int n) { return encode_from_val(n, 8); }
vector<char> dec_to_hexakaidecapus(int n) { return encode_from_val(n, 16); }

vector<char> septapus_to_dec(vector<char> s) { return encode_from_val(decode_to_val(s, 7), 10); }
vector<char> octopus_to_dec(vector<char> s) { return encode_from_val(decode_to_val(s, 8), 10); }
vector<char> hexakaidecapus_to_dec(vector<char> s) { return encode_from_val(decode_to_val(s, 16), 10); }

vector<char> septapus_to_octopus(vector<char> s) { return encode_from_val(decode_to_val(s, 7), 8); }
vector<char> septapus_to_hexakaidecapus(vector<char> s) { return encode_from_val(decode_to_val(s, 7), 16); }

// Mantenido el error tipográfico original de la firma ("octapus")
vector<char> octapus_to_septapus(vector<char> s) { return encode_from_val(decode_to_val(s, 8), 7); }
vector<char> octopus_to_hexakaidecapus(vector<char> s) { return encode_from_val(decode_to_val(s, 8), 16); }

vector<char> hexakaidecapus_to_septapus(vector<char> s) { return encode_from_val(decode_to_val(s, 16), 7); }
vector<char> hexakaidecapus_to_octopus(vector<char> s) { return encode_from_val(decode_to_val(s, 16), 8); }
