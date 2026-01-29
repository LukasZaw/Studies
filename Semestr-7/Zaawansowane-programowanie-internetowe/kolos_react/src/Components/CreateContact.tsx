import { useState } from "react";
import { Contact } from "../Model/Contact";
import { Email } from "../Model/Email";
import type { Category } from "../Model/Category";

type Props = {
  nextId: number;
  onContactCreated: (contact: Contact) => void;
};

const CreateContact = ({ nextId, onContactCreated }: Props) => {
  const [firstName, setFirstName] = useState("");
  const [lastName, setLastName] = useState("");
  const [age, setAge] = useState("");
  const [sex, setSex] = useState("0"); // 0 - M, 1 - K
  const [emailValue, setEmailValue] = useState("");
  const [emailCategory, setEmailCategory] = useState("Prywatne");

  const handleSubmit = (e: React.FormEvent<HTMLFormElement>) => {
    e.preventDefault();
    if (!firstName || !lastName || !age || !emailValue) {
      return;
    }

    const category: Category = {
      id: emailCategory === "Prywatne" ? 1 : 2,
      name: emailCategory,
    };

    const newContact = new Contact(
      nextId,
      firstName,
      lastName,
      Number(sex),
      [new Email(emailValue, category)],
      Number(age),
    );

    onContactCreated(newContact);

    setFirstName("");
    setLastName("");
    setAge("");
    setSex("0");
    setEmailValue("");
    setEmailCategory("Prywatne");
  };

  return (
    <div>
      <h2>Dodaj nowy kontakt</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <label>
            Imię:
            <input
              value={firstName}
              onChange={(e) => setFirstName(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>
            Nazwisko:
            <input
              value={lastName}
              onChange={(e) => setLastName(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>
            Wiek:
            <input
              type="number"
              value={age}
              onChange={(e) => setAge(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>
            Płeć:
            <select value={sex} onChange={(e) => setSex(e.target.value)}>
              <option value="0">Mężczyzna</option>
              <option value="1">Kobieta</option>
            </select>
          </label>
        </div>
        <div>
          <label>
            E-mail:
            <input
              type="email"
              value={emailValue}
              onChange={(e) => setEmailValue(e.target.value)}
            />
          </label>
        </div>
        <div>
          <label>
            Typ e-maila:
            <select
              value={emailCategory}
              onChange={(e) => setEmailCategory(e.target.value)}
            >
              <option value="Prywatne">Prywatne</option>
              <option value="Służbowe">Służbowe</option>
            </select>
          </label>
        </div>
        <button type="submit">Dodaj kontakt</button>
      </form>
    </div>
  );
};

export default CreateContact;
