# 💉 BloRidge - Blood Donation Match System

BloRidge is a real-world C++ console application designed to help donors and receivers connect based on **blood group compatibility**. It handles:

✅ Donor Registration  
✅ Blood Request & Auto-Matching  
✅ Contact Selection from Compatible Donors  
✅ File-based Data Persistence (donors.txt & receivers.txt)  
✅ Clean, user-friendly CLI experience

---

## 🚀 Features

- 🔄 **Instant Matching:** Matches blood requests to compatible donors in real time
- 🩸 **Full Blood Group Compatibility** (O-, O+, A-, A+, B-, B+, AB-, AB+)
- 💾 **Persistent Storage**: All donors and receivers saved in `.txt` files
- 🔐 **Duplicate Protection**: Prevents re-registration of same donor
- 📃 **Input Validation**: Case-insensitive, handles both `A+` and `a positive`
- ✅ **User Experience**: Clean prompts, numbered options, error-proof input

---

## 💻 How to Run

### Requirements:
- C++ Compiler (e.g., g++)
- Windows or Linux terminal

### Steps:

```bash
g++ BloRidge.cpp -o BloRidge.exe    # Compile
./BloRidge.exe                      # Run
