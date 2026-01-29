import type { Category } from "./Category";

export class Email {
  public get value(): string {
    return this._value;
  }
  public get category(): Category {
    return this._category;
  }

  private _value: string;
  private _category: Category;

  constructor(value: string, category: Category) {
    this._value = value;
    this._category = category;
  }
}
