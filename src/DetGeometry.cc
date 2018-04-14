

#include <G4Tubs.hh>
#include <G4UnionSolid.hh>
#include <G4SubtractionSolid.hh>
#include "DetGeometry.hh"

DetGeometry::DetGeometry() {
    world_sizeXYZ   = 50 * m;
    nist            = G4NistManager::Instance();
    world_mat       = nist->FindOrBuildMaterial("G4_AIR");
    solidWorld      = new G4Box("solWorld", 0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);
    logicWorld      = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
    physWorld       = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);

    G4cout<<"Geometry of detector is build successfully\t\t\t\t\t\tOK!!!"<<G4endl;
}

DetGeometry::~DetGeometry() {}

G4VPhysicalVolume* DetGeometry::Construct(){
    G4Box* box= new G4Box("box", 50, sqrt(3)/2*100, 50);
    G4Tubs* tubs = new G4Tubs("tubs", 0, 20, 200, 0, 360*deg);
    G4UnionSolid* union1= new G4UnionSolid("num", box, box, new G4RotationMatrix(60*deg,0,0), G4ThreeVector(0,0,0));
    G4UnionSolid* union2 = new G4UnionSolid("my_sub", union1, box, new G4RotationMatrix(120*deg,0,0), G4ThreeVector(0,0,0));
    G4SubtractionSolid* sub = new G4SubtractionSolid("sub", union2, tubs);

    G4LogicalVolume *sub_log = new G4LogicalVolume(sub, G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"), "logicWorld");
    //G4LogicalVolume(union2, G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"), "logicWorld");
    for (int i=0; i<6; i++){
        new G4PVPlacement(new G4RotationMatrix(15*i*deg,0,0), G4ThreeVector(0, 0, i*100), sub_log, "union_log", logicWorld, false, 0);

    }


    return physWorld;
}


