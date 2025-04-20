# Simple C++ MySQL Login App

A lightweight C++ app using **wxWidgets** and **MariaDB/MySQL** for basic user login.


## Preview

![image](https://github.com/user-attachments/assets/e5ca98c7-dfe4-4934-a592-6e9a28dd9280)



---

## Requirements

```bash
sudo apt-get install libmariadb-dev libwxgtk-gl3.2-1t64
```

---

## Build

```bash
mkdir build
cd build
cmake ..
make
```

---

## users Table

```sql
CREATE TABLE users (
    id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50),
    password VARCHAR(255)
);

INSERT INTO users (username, password) VALUES ('admin', 'secret');
```

---

## Files

- `Database.*` – handles DB connection & login check  
- `LoginFrame.*` – simple wxWidgets login form  
- `main.cpp` – app entry point  

---

## Tested On

- Ubuntu 22.04  
- GCC 11  
- MariaDB 10.x  
- wxWidgets 3.2  
