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



(0..200).each do |i|
	disp = displacement(i,i*1.2, ENCODER_SCALE_FACTOR)
	rot = rotation(i, i*1.2, ENCODER_SCALE_FACTOR, WHEELSEPARATION)
	heading = heading + rot
	posx = posx + disp * Math::cos(heading + rot/2)
	posy = posy + disp * Math::sin(heading + rot/2)
	puts "#{i},#{posx},#{posy}"

end
