# Student-Register
# Problem- Under this assignment you are required to create a suitable data-structure and associated functions for maintaining a simple student-register.
# The Student Register
# The Data Structure: 
The maximum number of entries (students) that the register should support is a predefined constant. Each entry (student) in the register should consist of the following fields.
  o name: a null-terminated string containing the last and first names separated by a comma, for example "Tagore, Rabindranath". This string cannot be empty.
  o roll: a 6 digit integer number unique for each student. A roll number cannot start with 0.
  o telephone: a null-terminated non-empty string containing a telephone number.
  o address: consists of null-terminated strings containing address. These strings can be empty.
# Associated Functions: Let SReg and Student be the user-defined data-types for a student-register and a student, respectively. The Student Register should support the following operations.
  o int add(SReg sr, Student s) – adds a new student s to the student register sr. A new student is a student for whom the roll does not already exist in the
    student register sr. If s already exists in sr (that is, the roll field of s matches with roll field of some entry of sr), the function returns 0, otherwise the
    function returns 1.
  o Student get(SReg sr, int r) – returns the student from sr whose roll field matches with r. If there is no such student in sr, the roll field of the returned        Student is 0.
  o int delete(SReg sr, int r) – deletes the student from sr whose roll field matches with r. If there is no such student in sr, the function returns 0; it returns     1 otherwise.
  o int modify(SReg sr, Student s) – updates the fields of an existing student of sr whose roll field matches with that of s, taking values from the
    corresponding fields of s. The function returns 0 if no such student exists in sr; otherwise it returns 1.
  o sortStudents(SReg sr) – sorts the students of the student register sr in alphabetically ascending order of names.
  o int getCount(SReg sr) – returns the number of students in the student register sr.
  o export(SReg sr, String fname) – saves the student register sr to a file having name fname.
  o load(SReg sr, String fname) – loads students in the student register sr from the file having name fname. Please note that a file generated by
    the export(SRef sr, String fname) function can be used by this function.
C - like syntax has been used in the above specification of the student register. Please note that they are just suggestive. You apply your own judgement in choosing the data types of the functions and there parameters.
