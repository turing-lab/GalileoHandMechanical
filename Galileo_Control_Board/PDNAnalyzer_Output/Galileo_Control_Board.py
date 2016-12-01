designFile = "D:/Workspace_Altium/Galileo_Control_Board/PDNAnalyzer_Output/Galileo_Control_Board.tgz"
powerNets = ["+VBAT"]
groundNets = ["GND"]
excitation = [["+VBAT", "J2", "1", "GND", "11", ""],
              ["+VBAT", "U4", "12", "GND", "", "0.5"],
              ["+VBAT", "U5", "12", "GND", "", "0.5"],
              ["+VBAT", "U6", "12", "GND", "", "0.5"]]
# Resistors / Inductors
passives = {}
# Material Properties:
tech = [
        {'name': 'TOPSOLDER', 'DielectricConstant': 3.5, 'Thickness': 1.016E-05},
        {'name': 'TOP', 'Conductivity': 58800000, 'Thickness': 3.556E-05},
        {'name': 'SUBSTRATE-1', 'DielectricConstant': 4.8, 'Thickness': 0.00032004},
        {'name': 'BOTTOM', 'Conductivity': 58800000, 'Thickness': 3.556E-05},
        {'name': 'BOTTOMSOLDER', 'DielectricConstant': 3.5, 'Thickness': 1.016E-05}
       ]
special_settings = {'removecutoutsize' : 7.8 }
plating_thickness = 0.7
finished_hole_diameters = True