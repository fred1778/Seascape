# Seascape
## Command-line archive management system build on top of SQLite

![1920px-Winslow_Homer_-_Sunlight_on_the_Coast_-_Google_Art_Project](https://github.com/user-attachments/assets/606b55cb-7897-4bf7-86c0-c81d516dcb5d)

---

Seascape stands for **State, Event, Aretefact** - the three interaltting domains that together paint a picture of life. It is useful foundation point for building archives, something I've always ffound alluring. The Seascape tools in this repo provide a command-line interface for interacting with a Seascape archive database - essentially a SQLite database with a table for each of the three types of entities (state, event, artefact). It compriaes a C++ program which ingests easy-to-write commands, and transforms these in to SQL queries using `sqlite3` C/C++ library to interact with the `seascape.db`. This program is supported by bash scripts that enable the archivist to collect artefacts as PDFs, list them in a text file, and perform bulk updates to create new entries linked via their identifier to PDFs in the `/archive` directory. 




