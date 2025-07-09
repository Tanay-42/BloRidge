# BloRidge - Blood Donation Match System

**BloRidge** is a real-world console-based C++ application that helps match blood donors with receivers based on blood group compatibility.

It provides:
- Real-time donor matching during blood requests
- Clean command-line interface
- File-based data persistence (`donors.txt`, `receivers.txt`)
- Input validation and duplicate detection

---

## Project Structure

```
BloRidge/
├── BloRidge.cpp         # Main source code
├── donors.txt           # Auto-generated donor records
├── receivers.txt        # Auto-generated receiver requests
└── README.md            # Project documentation
```

---

## How to Compile and Run

This project is written in standard C++. Use any C++11+ compiler.

### Windows

```bash
g++ BloRidge.cpp -o BloRidge.exe
BloRidge.exe
```

### Linux / macOS

```bash
g++ BloRidge.cpp -o BloRidge
./BloRidge
```

---

## Sample Usage

### 1. Registering Donors

```
========== BloRidge: Blood Donation System ==========
1. Register as Donor
2. Request Blood
3. View Donors
4. Exit
=======================================================
Enter choice: 1

Enter your name: Tanay

Valid blood groups: O-, O+, A-, A+, B-, B+, AB-, AB+
Enter blood group: O+
Enter contact info (e.g., phone or email): +918767579049

Donor registered successfully!
```

---

### 2. Requesting Blood

```
Enter choice: 2

Enter your name: Divya

Valid blood groups: O-, O+, A-, A+, B-, B+, AB-, AB+
Enter required blood group: AB-
Enter your contact info (e.g., phone or email): @krx

Searching for compatible donors...

Yes, donor(s) exist! Here are the details:
---------------------------------------------
1. Karan [O-], Contact: karan@example.com
---------------------------------------------

Enter the number of the donor to contact (0 to skip): 1

Contact this donor ASAP: Karan [O-], karan@example.com
```

---

### 3. Viewing All Donors

```
Enter choice: 3

Registered Donors:
---------------------------------------------
1. Tanay (O+), Contact: +918767579049
2. Karan (O-), Contact: karan@example.com
---------------------------------------------
```

---

### 4. Sample: Request with No Matches

```
Enter choice: 2

Enter your name: Mayank
Enter required blood group: A-
Enter your contact info: mayank@xmail.com

Searching for compatible donors...

No compatible donors found at the moment.
Your request has been recorded. We'll notify you when a match is found.
```

---

## Features

- Validates all blood groups (O-, O+, A-, A+, B-, B+, AB-, AB+)
- Accepts aliases like "O Negative", "A Positive", etc.
- Case-insensitive and whitespace-tolerant inputs
- Prevents duplicate donor registrations
- Provides instant donor match suggestions during blood requests

---

## Future Enhancements

- Web UI (React/Firebase or Flask)
- Location-based filtering and search
- Email/SMS notifications for matches
- Admin dashboard for moderation
- Cloud-hosted database (e.g., Firebase/MongoDB)

---

## Author

**Tanay Verma**  
Email: tanayverma42004@gmail.com  
GitHub: [@tanayverma](https://github.com/tanayverma)  
LinkedIn: [linkedin.com/in/tanay-verma](https://linkedin.com/in/tanay-verma)

---

## License

This project is open-source and free to use. You may extend it for NGOs, hospitals, or educational purposes.

