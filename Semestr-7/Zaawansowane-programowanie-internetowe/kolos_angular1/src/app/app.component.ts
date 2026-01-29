import { Component } from "@angular/core";
import { ListComponent } from "./list/list.component";

@Component({
  selector: "app-root",
  standalone: true,
  imports: [ListComponent],
  template: `
    <h1>Welcome to {{ title }}!</h1>
    <app-list></app-list>
  `,
  styles: [],
})
export class AppComponent {
  title = "kolos_angular1";
}
