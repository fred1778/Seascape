# Seascape
## Command-line archive management system build on top of SQLite (WIP)

![1920px-Winslow_Homer_-_Sunlight_on_the_Coast_-_Google_Art_Project](https://github.com/user-attachments/assets/606b55cb-7897-4bf7-86c0-c81d516dcb5d)
A Seascape - *Sunlight on the Coast*, Winslow Homer, 1890


---
Seascape stands for **State, Event, Aretefact** - the three interaltting domains that together paint a picture of life. It is useful foundation point for building archives, something I've always ffound alluring. The Seascape tools in this repo provide a command-line interface for interacting with a Seascape archive database - essentially a SQLite database with a table for each of the three types of entities (state, event, artefact). It comprises a C++ program which ingests easy-to-write commands, and transforms these in to SQL queries using `sqlite3` C/C++ library to interact with the `seascape.db`. This program is supported by shell scripts that enable the archivist to collect artefacts as PDFs, list them in a text file, and perform bulk updates to create new entries linked via their identifier to PDFs in the `/archive` directory. 

Seascape is designed to minimise overhead and maximise portability - in my implementation, I use a 4GB Raspberry Pi 5 with a 1 TB SSD to store the database and archived material and run Seascape on the standard raspi os Linux distro. This provides a scalable foundatrion for using Seascape to drive a local (or public) server for interacting with the archive.



## SEA Taxonomy
The below table summaries the database fields used in the Seascape schema and command input. Several fields are shared across two or all of the different tables. The associated C++ objects created to represent entities transform and expand upon some of these attributes to aid querying, for instance, keyDate is transormed into a `struct tm` structure and a `timeframe` property to indicate the intended precision of the date (day, month, year).

| Field | Type in DB | Description | Scope |
|-------|------|-------------|-------|
|`seacode`| Text | **Primary Key** Unique identifer assigned to every entity across domains, prefixed with the domain (S,E,A) and the type code, e.g. A11 -> 'Artefact, ocassion inbound' (birtdhay cards, etc.)|S,E,A|
|`keyDate`| Integer | A 1 to 6 digit integer representing the 'key date' for the entity in a flexible DDMMYY form, depending on how many digits are provided: '96' refers to simply 1996, '496' translates to 'April 1996', '120496' refers to 12th April 1996. As the command is initially handled as a string, users can pad with zeros to make their inputs more readable (e.g. 000596 instead of the underlying integer value, 596). In my implenetation, designed to archive my life, I impose a 'Y2k96' limitation on my archive in which 96 will be interpreted as 1996, 0 maps to 2000, and 95 maps to 2095. Other implementations could easily have four digits for the year to avoid the 99-year cap.|A|
|`form`| Text | An indicator to represent the form of an artefact - can be adpated but currently used to identify physical artefacts (P) and digital artefacts (D), as this has ramifications for how an artefact is handled |A|
|`type`| Text | A two-digit identifier for the category of the entity relative to its domain. Flexible in how this can be implemented but typical approach would be, for instance, 1x = correspondence such that 11 is cards, 12 is letters, etc. | S, E, A |
|`name`| Text | A short name for the entity - e.g. *Birthday card from X* or *Holiday to Y* |S, E, A|
|`desc`| Text | A description for the entity - e.g. *Card includes reference to Y and depcits image of X* |S, E, A|
|`rubicon`| Integer | A value representing the confidentially of the archive, 1 being public, and up to 3 (at present). Useful for informing permissions for files and controlling different users' level of access|S, E, A|
|`eventID`| Text | A foreign key to associate an entity with a specific event - for example, birthday cards for a 12th birthday are assoicated with the ID for the 'twelth birthday' event. |A|
|`location`| Text | The location of a physical artefact | A |


## Using Seascape


The executable takes one arguement - a command to be executed. Commands are structured as follows:

`opcode/cmdpart/cmdpart/..`

For example, to insert a new artefact, use the `IA` (insert artefact) opcode followed by the values for the fields seperated by `/`, for example:

`IA/./000315/D/Essay on Humanism/Essay written for week 3 of term on the topic of Humanism in the Renaissance/1/X/31/X`

The use of `/./` means 'delegate the population of this field to the program'. Currently, as above, this is used to instruct the program to generate a valid `seacode` for this new entity. The use of `X` indicates that this field is not applicable.

The scripts `evgo` (event go) and `argo` (artefact go) provide a conveinient way to bulk add events and artefacts respectivley by simply listing commands in a text file (`manidfest.txt` or `events.txt`). For artefacts, the script will use the program output for each command (which if succesful will be the new entry's `seacode`) to rename the top `.pdf` file in `/staging` directory to the new seacode, and move it in to the `\archive` directory. This means that an archivist can scan artefacts and record their data in a simple text file and then simply submit these to the Seascape together.

### Querying

Seascpae uses a set of commands that represent common archive-based queries. Query commands are specified by Q-type opcodes (e.g. `QA` for artefact queries). Each query opcode has a set of built-in queries for common tasks, for instance:

`QA/ofevent` - get all artefacts the relate to the following event seacode, for example `QA/ofevent/E123456`. This maps to the SQL command `SELECT * FROM artefacts WHERE event=E123456`.














