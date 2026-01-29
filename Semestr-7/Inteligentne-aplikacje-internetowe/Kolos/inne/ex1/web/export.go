package web

import (
	"encoding/json"
	"grp/kmeans"
	"net/http"
	"strconv"
)

func exportFunc(w http.ResponseWriter, r *http.Request) {
	// obtain value from path /export/{pts}/{cls}
	ptf := r.PathValue("pts")
	clf := r.PathValue("cls")
	pts, er1 := strconv.Atoi(ptf)
	cls, er2 := strconv.Atoi(clf)
	// check errors
	if er1 != nil || er2 != nil || pts < 2 || cls < 2 || pts > 10000 || cls > 5000 || cls >= pts {
		http.Error(w, "inorect request", http.StatusBadRequest)
		return
	}
	// group points and return page
	k := kmeans.NewKMeans(pts, cls, 3)
	for range 20 {
		k.Iterate()
	}
	e := k.Export()
	w.Header().Set("Content-type", "application/json")
	res, _ := json.Marshal(e)
	w.Write(res)
}
