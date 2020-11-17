package wolf

type wolf struct {
	wolfName   string
	wolfWisdom string //replace with type wisdom.go later
}

func createNewWolfInstance(newWolfName string, initialWisdom string) wolf {

	var defaultWisdom = "Wolf is stronger than lion but does not perform in circus"
	w := wolf{wolfName: newWolfName, wolfWisdom: defaultWisdom}
	return w
}
