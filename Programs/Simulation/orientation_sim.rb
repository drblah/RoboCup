def displacement(leftEncoder, rightEncoder, encoderScale)
	return (leftEncoder + rightEncoder) * encoderScale / 2
end

def rotation(leftEncoder, rightEncoder, encoderScale, track)
	return (leftEncoder - rightEncoder) * encoderScale / track
end

posx = 0
posy = 0
heading = 0

WHEELSIZE = 7
ENCODER_COUNT_REVOLUTION = 360
ENCODER_SCALE_FACTOR = ((Math::PI*WHEELSIZE)/ENCODER_COUNT_REVOLUTION)
WHEELSEPARATION = 15

(0..100).each do |i|
	posx = posx + displacement(i,i, ENCODER_SCALE_FACTOR) * Math::cos(heading + rotation(i, i*0.7, ENCODER_SCALE_FACTOR, WHEELSEPARATION)/2)
	posy = posy + displacement(i,i, ENCODER_SCALE_FACTOR) * Math::sin(heading + rotation(i, i*0.7, ENCODER_SCALE_FACTOR, WHEELSEPARATION)/2)
	puts "#{i},#{posx},#{posy}"
end

#puts "Reversing"

(0..99).each do |i|
	ir = 100-i

	posx = posx + displacement(ir,ir, ENCODER_SCALE_FACTOR) * Math::cos(heading + rotation(ir, ir*0.7, ENCODER_SCALE_FACTOR, WHEELSEPARATION)/2)
	posy = posy + displacement(ir,ir, ENCODER_SCALE_FACTOR) * Math::sin(heading + rotation(ir, ir*0.7, ENCODER_SCALE_FACTOR, WHEELSEPARATION)/2)
	puts "#{i},#{posx},#{posy}"
end
