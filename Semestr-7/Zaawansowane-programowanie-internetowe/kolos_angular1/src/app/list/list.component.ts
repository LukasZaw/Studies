import { Component, OnInit } from "@angular/core";
import { CommonModule } from "@angular/common";
import { FormsModule } from "@angular/forms";

interface Person {
  firstName: string;
  lastName: string;
  age: number;
  email: string;
}

@Component({
  selector: "app-list",
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: "./list.component.html",
  styles: [],
})
export class ListComponent implements OnInit {
  people: Person[] = [];

  // pola formularza
  newFirstName = "";
  newLastName = "";
  newAge: number | null = null;
  newEmail = "";
  editingIndex: number | null = null;

  addPerson(): void {
    if (
      !this.newFirstName ||
      !this.newLastName ||
      !this.newAge ||
      !this.newEmail
    ) {
      return;
    }

    const newPerson: Person = {
      firstName: this.newFirstName,
      lastName: this.newLastName,
      age: this.newAge,
      email: this.newEmail,
    };

    if (this.editingIndex !== null) {
      this.people = this.people.map((person, index) =>
        index === this.editingIndex ? newPerson : person,
      );
    } else {
      this.people = [...this.people, newPerson];
    }

    this.newFirstName = "";
    this.newLastName = "";
    this.newAge = null;
    this.newEmail = "";
    this.editingIndex = null;
  }

  removePerson(index: number): void {
    this.people = this.people.filter((_, i) => i !== index);
  }

  ngOnInit(): void {
    this.people = [
      {
        firstName: "Jan",
        lastName: "Kowalski",
        age: 30,
        email: "jan.kowalski@example.com",
      },
      {
        firstName: "Anna",
        lastName: "Nowak",
        age: 25,
        email: "anna.nowak@example.com",
      },
      {
        firstName: "Piotr",
        lastName: "Wiśniewski",
        age: 40,
        email: "piotr.wisniewski@example.com",
      },
    ];
  }

  editPerson(index: number): void {
    const person = this.people[index];
    if (!person) {
      return;
    }

    this.newFirstName = person.firstName;
    this.newLastName = person.lastName;
    this.newAge = person.age;
    this.newEmail = person.email;
    this.editingIndex = index;
  }

  cancelEdit(): void {
    this.newFirstName = "";
    this.newLastName = "";
    this.newAge = null;
    this.newEmail = "";
    this.editingIndex = null;
  }
}
