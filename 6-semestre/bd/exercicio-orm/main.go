package main

import (
	"fmt"
	"log"
	"os"
	"time"

	"gorm.io/driver/mysql"
	"gorm.io/driver/postgres"
	"gorm.io/driver/sqlite"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"
)

type BaseModel struct {
	ID        uint `gorm:"primaryKey"`
	CreatedAt time.Time
	UpdatedAt time.Time
}

type Person struct {
	BaseModel
	FirstName string  `gorm:"size:100;not null"`
	LastName  string  `gorm:"size:100;not null"`
	Email     *string `gorm:"size:255;"`
}

type Employee struct {
	Person
	EmployeeNumber string `gorm:"size:50;not null;unique"`
	HireDate       time.Time
	DepartmentID   uint
}

type Department struct {
	BaseModel
	Name        string `gorm:"size:150;not null"`
	Description *string
	Location    string `gorm:"size:100;not null"`
}

type Project struct {
	BaseModel
	Title   string `gorm:"size:200;not null"`
	Budget  int64
	Started time.Time
}

type Task struct {
	BaseModel
	ProjectID   uint
	Title       string `gorm:"size:200;not null"`
	Description *string
}

type Tag struct {
	BaseModel
	Key   string `gorm:"size:100;not null"`
	Value string `gorm:"size:255"`
}

type Asset struct {
	BaseModel
	OwnerID uint
	Name    string `gorm:"size:150;not null"`
	Serial  *string
}

type LogEntry struct {
	BaseModel
	Source  string `gorm:"size:120;not null"`
	Message string `gorm:"type:text"`
	Level   string `gorm:"size:20;not null"`
}

type Audit struct {
	BaseModel
	Entity   string `gorm:"size:120;not null"`
	EntityID uint
	Action   string `gorm:"size:50;not null"`
}

type User struct {
	BaseModel
	Username string  `gorm:"size:100;not null;unique"`
	Password string  `gorm:"size:255;not null"`
	Bio      *string `gorm:"type:text"`
}

func connect(driver string, dsn string) (*gorm.DB, error) {
	cfg := &gorm.Config{
		Logger: logger.Default.LogMode(logger.Info),
	}
	switch driver {
	case "sqlite":
		return gorm.Open(sqlite.Open(dsn), cfg)
	case "mysql":
		return gorm.Open(mysql.Open(dsn), cfg)
	case "postgres":
		return gorm.Open(postgres.Open(dsn), cfg)
	default:
		return nil, fmt.Errorf("unsupported driver: %s", driver)
	}
}

func migrate(db *gorm.DB) error {
	return db.AutoMigrate(
		&Person{}, &Employee{}, &Department{}, &Project{}, &Task{}, &Tag{}, &Asset{}, &LogEntry{}, &Audit{}, &User{},
	)
}

func seed(db *gorm.DB) error {
	email1 := "alice@example.com"
	email2 := "bob@example.com"
	p1 := Person{FirstName: "Alice", LastName: "Anderson", Email: &email1}
	p2 := Person{FirstName: "Bob", LastName: "Brown", Email: &email2}
	if err := db.Create(&p1).Error; err != nil {
		return err
	}
	if err := db.Create(&p2).Error; err != nil {
		return err
	}

	desc1 := "Eng Department"
	dept1 := Department{Name: "Engineering", Description: &desc1, Location: "Building A"}
	dept2 := Department{Name: "HR", Description: nil, Location: "Building B"}
	if err := db.Create(&dept1).Error; err != nil {
		return err
	}
	if err := db.Create(&dept2).Error; err != nil {
		return err
	}

	hire1 := time.Now().AddDate(-2, 0, 0)
	hire2 := time.Now().AddDate(-1, 0, 0)
	e1 := Employee{Person: p1, EmployeeNumber: "E1001", HireDate: hire1, DepartmentID: dept1.ID}
	e2 := Employee{Person: p2, EmployeeNumber: "E1002", HireDate: hire2, DepartmentID: dept2.ID}
	if err := db.Create(&e1).Error; err != nil {
		return err
	}
	if err := db.Create(&e2).Error; err != nil {
		return err
	}

	proj1 := Project{Title: "Project Alpha", Budget: 100000, Started: time.Now().AddDate(-1, 0, 0)}
	proj2 := Project{Title: "Project Beta", Budget: 50000, Started: time.Now().AddDate(-2, 0, 0)}
	if err := db.Create(&proj1).Error; err != nil {
		return err
	}
	if err := db.Create(&proj2).Error; err != nil {
		return err
	}

	d1 := "Implement API"
	t1 := Task{ProjectID: proj1.ID, Title: "API", Description: &d1}
	t2 := Task{ProjectID: proj2.ID, Title: "Docs", Description: nil}
	if err := db.Create(&t1).Error; err != nil {
		return err
	}
	if err := db.Create(&t2).Error; err != nil {
		return err
	}

	tag1 := Tag{Key: "env", Value: "prod"}
	tag2 := Tag{Key: "priority", Value: "high"}
	if err := db.Create(&tag1).Error; err != nil {
		return err
	}
	if err := db.Create(&tag2).Error; err != nil {
		return err
	}

	serial := "SN-12345"
	asset1 := Asset{OwnerID: p1.ID, Name: "Laptop", Serial: &serial}
	asset2 := Asset{OwnerID: p2.ID, Name: "Monitor", Serial: nil}
	if err := db.Create(&asset1).Error; err != nil {
		return err
	}
	if err := db.Create(&asset2).Error; err != nil {
		return err
	}

	log1 := LogEntry{Source: "system", Message: "Started", Level: "INFO"}
	log2 := LogEntry{Source: "scheduler", Message: "Job done", Level: "INFO"}
	if err := db.Create(&log1).Error; err != nil {
		return err
	}
	if err := db.Create(&log2).Error; err != nil {
		return err
	}

	a1 := Audit{Entity: "User", EntityID: 1, Action: "create"}
	a2 := Audit{Entity: "Project", EntityID: proj1.ID, Action: "update"}
	if err := db.Create(&a1).Error; err != nil {
		return err
	}
	if err := db.Create(&a2).Error; err != nil {
		return err
	}

	bio := "I am a sample user"
	u1 := User{Username: "user1", Password: "pass", Bio: &bio}
	u2 := User{Username: "user2", Password: "pass", Bio: nil}
	if err := db.Create(&u1).Error; err != nil {
		return err
	}
	if err := db.Create(&u2).Error; err != nil {
		return err
	}

	return nil
}

func main() {
	driver := os.Getenv("DB_DRIVER")
	if driver == "" {
		driver = "sqlite"
	}
	dsn := os.Getenv("DB_DSN")
	fmt.Println("Using driver:", driver)
	fmt.Println("Using DSN:", dsn)
	if dsn == "" {
		dsn = "file::memory:?cache=shared"
	}

	db, err := connect(driver, dsn)
	if err != nil {
		log.Fatalf("connect: %v", err)
	}

	if err := migrate(db); err != nil {
		log.Fatalf("migrate: %v", err)
	}

	if err := seed(db); err != nil {
		log.Fatalf("seed: %v", err)
	}

	fmt.Println("Migration and seeding complete")
}
