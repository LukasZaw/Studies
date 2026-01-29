import { Email } from "./Email";

export class Contact {
  public id: number;
  public firstName: string;
  public lastName: string;
  public sex: number;
  public emails: Email[];
  public age: number;

  constructor(
    id: number,
    firstName: string,
    lastName: string,
    sex: number,
    emails: Email[],
    age: number,
  ) {
    this.id = id;
    this.firstName = firstName;
    this.lastName = lastName;
    this.sex = sex;
    this.emails = emails;
    this.age = age;
  }
}

// Przykładowe dane
import type { Category } from "./Category";

const privateCategory: Category = { id: 1, name: "Prywatne" };
const workCategory: Category = { id: 2, name: "Służbowe" };

export const sampleContacts: Contact[] = [
  new Contact(
    1,
    "Jan",
    "Kowalski",
    0,
    [new Email("jan.kowalski@przyklad.pl", privateCategory)],
    30,
  ),
  new Contact(
    2,
    "Anna",
    "Nowak",
    1,
    [
      new Email("anna.nowak@firma.pl", workCategory),
      new Email("anna.nowak@przyklad.pl", privateCategory),
    ],
    25,
  ),
  new Contact(
    3,
    "Tomasz",
    "Nowak",
    0,
    [new Email("tomasz.nowak@przyklad.pl", privateCategory)],
    40,
  ),
];
