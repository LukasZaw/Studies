import { NgModule } from "@angular/core";
import { BrowserModule } from "@angular/platform-browser";
import { FormsModule } from "@angular/forms";

import { AppRoutingModule } from "./app-routing.module";
import { AppComponent } from "./app.component";

@NgModule({
  declarations: [],
  imports: [BrowserModule, AppRoutingModule, FormsModule, AppComponent],
  providers: [],
  bootstrap: [AppComponent],
})
export class AppModule {}
