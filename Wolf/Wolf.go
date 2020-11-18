package Wolf

type Wolf struct {
	name   string
	wisdom string //replace with type wisdom.go later
}

func defaultWolf(newWolfName string) *Wolf {

	var defaultWisdom = "Wolf is stronger than lion but does not perform in circus"
	w := Wolf{name: newWolfName, wisdom: defaultWisdom}
	return &w
}
