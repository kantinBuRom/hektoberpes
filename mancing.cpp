#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>   // Untuk timing
#include <thread>   // Untuk jeda (sleep)
#include <random>   // Untuk generator angka acak yang lebih baik
#include <limits>   // Untuk std::numeric_limits

// --- Struktur Data ---

// Mendefinisikan seekor ikan
struct Fish {
    std::string name;
    std::string rarity; // "Biasa", "Langka", "Legendaris"
};

// --- Variabel Global & Pengaturan Awal ---

// Daftar semua ikan yang bisa ditangkap
std::vector<Fish> fishDatabase = {
    {"Ikan Lele", "Biasa"},
    {"Ikan Nila", "Biasa"},
    {"Ikan Mujair", "Biasa"},
    {"Sepatu Butut", "Sampah"}, // Bukan ikan, tapi hasil pancingan
    {"Ikan Mas", "Biasa"},
    {"Ikan Gurame", "Langka"},
    {"Ikan Gabus", "Langka"},
    {"Kaleng Berkarat", "Sampah"},
    {"Belut Listrik", "Langka"},
    {"Ikan Arwana", "Legendaris"},
    {"Ikan Koi Emas", "Legendaris"}
};

// Tempat menyimpan koleksi ikan pemain
std::map<std::string, int> fishCollection;

// --- Fungsi Bantu ---

void bersihkanLayar() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void garisPemisah() {
    std::cout << "\n--------------------------------------------------\n";
}

void jedaSingkat(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

// Mendapatkan ikan acak berdasarkan keberuntungan
Fish getRandomCatch() {
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dist(1, 100);
    int roll = dist(rng);

    if (roll <= 5) { // 5% kesempatan Legendaris
        std::vector<Fish> legendary;
        for (const auto& fish : fishDatabase) {
            if (fish.rarity == "Legendaris") legendary.push_back(fish);
        }
        return legendary[dist(rng) % legendary.size()];
    }
    if (roll <= 25) { // 20% kesempatan Langka
        std::vector<Fish> rare;
        for (const auto& fish : fishDatabase) {
            if (fish.rarity == "Langka") rare.push_back(fish);
        }
        return rare[dist(rng) % rare.size()];
    }
    if (roll <= 75) { // 50% kesempatan Biasa
        std::vector<Fish> common;
        for (const auto& fish : fishDatabase) {
            if (fish.rarity == "Biasa") common.push_back(fish);
        }
        return common[dist(rng) % common.size()];
    }
    // Sisanya (25%) dapat Sampah
    std::vector<Fish> junk;
    for (const auto& fish : fishDatabase) {
        if (fish.rarity == "Sampah") junk.push_back(fish);
    }
    return junk[dist(rng) % junk.size()];
}

// --- Fungsi Utama Game ---

void showCollection() {
    bersihkanLayar();
    garisPemisah();
    std::cout << "--- KOLEKSI IKAN TANGKAPANMU ---\n";
    if (fishCollection.empty()) {
        std::cout << "Kamu belum menangkap apa-apa. Ayo mancing!\n";
    } else {
        for (const auto& pair : fishCollection) {
            std::cout << "- " << pair.first << ": " << pair.second << " ekor\n";
        }
    }
    garisPemisah();
    std::cout << "(Tekan Enter untuk kembali...)";
    std::cin.get();
}

void goFishing() {
    bersihkanLayar();
    garisPemisah();
    std::cout << "Kamu melempar kail ke tengah danau yang tenang...\n";
    std::cout << "Sekarang, tunggu dengan sabar...\n";
    garisPemisah();

    // Waktu tunggu acak antara 3 sampai 8 detik
    static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> waitDist(3000, 8000);
    jedaSingkat(waitDist(rng));

    // Momen kritis!
    std::cout << "\n!!! ADA SAMBARAN !!!\n";
    std::cout << "TEKAN [ENTER] SEKARANG UNTUK MENARIKNYA!\n";

    auto startTime = std::chrono::high_resolution_clock::now();
    std::cin.get(); // Menunggu pemain menekan Enter
    auto endTime = std::chrono::high_resolution_clock::now();

    // Hitung waktu reaksi pemain
    std::chrono::duration<double, std::milli> reactionTime = endTime - startTime;

    // Tentukan hasil berdasarkan waktu reaksi
    if (reactionTime.count() < 100) { // Kurang dari 0.1 detik
        std::cout << "\nTerlalu cepat! Kamu menarik kail sebelum ikan benar-benar terkait. Ikannya lepas!\n";
    } else if (reactionTime.count() > 1500) { // Lebih dari 1.5 detik
        std::cout << "\nTerlalu lambat! Ikannya sudah kabur membawa umpanmu!\n";
    } else {
        // Berhasil!
        std::cout << "\nDAPAT! Kamu berhasil menariknya!\n";
        jedaSingkat(1000);
        Fish caughtFish = getRandomCatch();
        std::cout << "Kamu mendapatkan: " << caughtFish.name << " (" << caughtFish.rarity << ")!\n";
        
        // Tambahkan ke koleksi
        fishCollection[caughtFish.name]++;
    }

    garisPemisah();
    std::cout << "(Tekan Enter untuk melanjutkan...)";
    // Membersihkan buffer input jika ada sisa input dari sebelumnya
    if (std::cin.peek() != '\n') {
       std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


int main() {
    std::cout << "=======================================\n";
    std::cout << "||    PETUALANGAN MANCING MANIA      ||\n";
    std::cout << "=======================================\n";
    std::cout << "Selamat datang di danau! Semoga beruntung!\n";
    std::cout << "(Tekan Enter untuk memulai...)\n";
    std::cin.get();

    std::string pilihan;
    while (true) {
        bersihkanLayar();
        garisPemisah();
        std::cout << "Apa yang ingin kamu lakukan?\n";
        std::cout << "[1] Mancing\n";
        std::cout << "[2] Lihat Koleksi Ikan\n";
        std::cout << "[3] Berhenti Mancing (Keluar)\n";
        garisPemisah();
        std::cout << "> ";
        std::getline(std::cin, pilihan);

        if (pilihan == "1") {
            goFishing();
        } else if (pilihan == "2") {
            showCollection();
        } else if (pilihan == "3") {
            std::cout << "Terima kasih sudah bermain! Sampai jumpa lagi!\n";
            break;
        } else {
            std::cout << "Pilihan tidak valid. Coba lagi.\n";
            jedaSingkat(1000);
        }
    }

    return 0;
}
